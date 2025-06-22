// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class TWODPROJECT_API AEnemyCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:

	AEnemyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	/** Health System */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		bool isDead;

	void Die();
	void OnDeathComplete();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
		void TakeDamage(float DamageAmount);
};
