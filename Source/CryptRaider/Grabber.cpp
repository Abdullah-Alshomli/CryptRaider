// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();





}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}


void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	bool HasHit;
	FHitResult HitResult;
	GetGrabbableInReach(HasHit, HitResult);

	if (HasHit)
	{
		AActor* GrabbedItem = HitResult.GetActor();
		if (GrabbedItem->ActorHasTag("stat"))
		{
			HitResult.GetComponent()->SetSimulatePhysics(true);
		}


		GrabbedItem->Tags.Add("Grabbed");
		UPrimitiveComponent* PrimitiveComponent = HitResult.GetComponent();
		PrimitiveComponent->WakeAllRigidBodies();


		GrabbedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			PrimitiveComponent,
			NAME_None,
			HitResult.ImpactPoint,
			PrimitiveComponent->GetComponentRotation()
		);
	}
}

void UGrabber::GetGrabbableInReach(bool& HasHit, FHitResult& HitResult)
{
	//drawing a debug line
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * GrabberMaxDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Purple, false, 5);

	// getting the collision
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();


	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();

		AActor* GrabbedItem = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedItem->Tags.Remove("Grabbed");

		PhysicsHandle->ReleaseComponent();


	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Pointer for Physics Handle"));
	}
	return Result;
}

