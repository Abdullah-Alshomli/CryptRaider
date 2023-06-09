// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Mover.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "TriggerComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetAcceptableActor();



protected:
// Called when the game starts
	virtual void BeginPlay() override;




private:
	UFUNCTION(BlueprintCallable)
		void SetMover(UMover* Mover);

	UPROPERTY(EditAnywhere)
		FName ActvatingTag;


	UMover* Mover;

};
