#include "CrabEnemy.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UCrabEnemy::UCrabEnemy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCrabEnemy::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetOwner()->GetActorLocation();
}

void UCrabEnemy::MoveEnemy()
{
	FVector newLocation = GetOwner()->GetActorLocation();
	newLocation.Y += moveSpeed * moveDirection * GetWorld()->GetDeltaSeconds();
	GetOwner()->SetActorLocation(newLocation);
}

void UCrabEnemy::CheckForTurn()
{
	FVector currentLocation = GetOwner()->GetActorLocation();
	float distanceTraveled = FMath::Abs(currentLocation.Y - startLocation.Y);

	if (distanceTraveled >= patrolDistance)
	{
		moveDirection *= -1;

		FVector scale = GetOwner()->GetActorScale3D();
		scale.Y *= -1;
		GetOwner()->SetActorScale3D(scale);
	}
}

// Called every frame
void UCrabEnemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveEnemy();
	CheckForTurn();
}

