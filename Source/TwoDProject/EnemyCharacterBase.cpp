// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"
#include "PaperCharacter.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
	isDead = false;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComponent = GetSprite();

	if (!FlipbookComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("FlipbookComponent not found! Make sure it's added in the Blueprint."));
	}

	UpdateAnimation();
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimation();

}

void AEnemyCharacterBase::UpdateAnimation()
{
	float Velocity = GetVelocity().SizeSquared();
	FString VelocityText = FString::Printf(TEXT("Velocity: X=%.2f, Y=%.2f, Z=%.2f"), Velocity);
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Green, VelocityText);
	if (GetVelocity().SizeSquared() == 0) // idle
	{
		FlipbookComponent->SetFlipbook(IdleAnimation);
	}
	else if (isDead)//death
	{
		FlipbookComponent->SetFlipbook(DeathAnimation);
	}
	else 
	{
		FlipbookComponent->SetFlipbook(RunAnimation);
	}
}


void AEnemyCharacterBase::TakeDamage(float DamageAmount)
{
	if (Health <= 0.0f) return;  // Already dead, ignore further damage

	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		isDead = true;
		Die();
	}
}

void AEnemyCharacterBase::Die()
{

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
		Destroy();
	});

}

void AEnemyCharacterBase::OnDeathComplete()
{
	Destroy();
}


