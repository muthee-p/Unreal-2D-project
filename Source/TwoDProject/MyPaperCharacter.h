// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "MyPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TWODPROJECT_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPaperCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	void UpdateAnimation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook* JumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook* CarryAnimation;

	/** Health System */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Carry")
		bool isCarrying;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void UpdateHealthWidget();

	void Die();
	void StopMovement();
	void OnDeathComplete();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
		void TakeDamage(float DamageAmount);
};
