// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OrignalLocation = GetOwner()->GetActorLocation();


}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OrignalLocation + MoveOffset;
		float Speed = FVector::Distance(CurrentLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}

	else
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		float Speed = FVector::Distance(CurrentLocation, OrignalLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OrignalLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}

}

void UMover::SetShouldMove(bool Boolean)
{
	ShouldMove = Boolean;
}

