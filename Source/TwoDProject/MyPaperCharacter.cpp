// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperCharacter.h"
#include "TimerManager.h"

AMyPaperCharacter::AMyPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
	isDead = false;
	isCarrying = false;
}

void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComponent = GetSprite();

	if (!FlipbookComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("FlipbookComponent not found! Make sure it's added in the Blueprint."));
	}

	UpdateAnimation();
}

void AMyPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimation();

}

void AMyPaperCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);

		if (FlipbookComponent)
		{
			FVector NewScale = FlipbookComponent->GetRelativeScale3D();
			NewScale.X = (Value < 0) ? 1.0f : -1.0f;
			FlipbookComponent->SetRelativeScale3D(NewScale);
		}
	}
}

void AMyPaperCharacter::UpdateAnimation()
{
	if (GetCharacterMovement()->IsFalling()) // Jumping
	{
		FlipbookComponent->SetFlipbook(JumpAnimation);
	}
	else if (!isCarrying && GetVelocity().SizeSquared() > 0) // Running
	{
		FlipbookComponent->SetFlipbook(RunAnimation);
	}
	else if (isDead)//death
	{
		FlipbookComponent->SetFlipbook(DeathAnimation);
	}
	else if (isCarrying && GetVelocity().SizeSquared() > 0)
	{
		FlipbookComponent->SetFlipbook(CarryAnimation);
	}
	else // Idle
	{
		FlipbookComponent->SetFlipbook(IdleAnimation);
	}
}


void AMyPaperCharacter::TakeDamage(float DamageAmount)
{
	if (Health <= 0.0f) return;  // Already dead, ignore further damage

	Health -= DamageAmount;
	//UE_LOG(LogTemp, Warning, TEXT("Player took damage! Health: %f"), Health);

	UpdateHealthWidget();

	if (Health <= 0.0f)
	{
		isDead = true;
		Die();
	}
}

void AMyPaperCharacter::Die()
{
	UE_LOG(LogTemp, Error, TEXT("Player has died!"));

	StopMovement();

	// Destroy after 2 seconds
	FTimerHandle DeathTimer;
	FTimerDelegate DeathDelegate;
	DeathDelegate.BindUObject(this, &AMyPaperCharacter::OnDeathComplete);  // Bind delegate to function
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, DeathDelegate, 2.0f, false);
	
}
void AMyPaperCharacter::OnDeathComplete()
{
	UE_LOG(LogTemp, Error, TEXT("Death process complete. Destroying character."));
	Destroy();
}

void AMyPaperCharacter::StopMovement()
{
	DisableInput(nullptr);

	// Stop all velocity
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);
}

void AMyPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPaperCharacter::MoveRight);
}
