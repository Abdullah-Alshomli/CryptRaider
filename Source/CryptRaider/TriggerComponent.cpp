// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called each frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor == nullptr)
	{
		Mover->SetShouldMove(false);
	}
	else
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

		if (Component)
		{
			Component->SetSimulatePhysics(false);
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		}

		Mover->SetShouldMove(true);
	}

}

AActor* UTriggerComponent::GetAcceptableActor()
{
	TArray<AActor*> ActorsArray;
	GetOverlappingActors(ActorsArray);

	for (AActor* Actor : ActorsArray)
	{
		if (Actor->ActorHasTag(ActvatingTag) && !(Actor->ActorHasTag("Grabbed")))
		{
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}




