// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericEnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "PestilenceOverlapActor.generated.h"

UCLASS()
class GROUP15_API APestilenceOverlapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APestilenceOverlapActor();

	UPROPERTY(EditAnywhere, Category = "Custom Parameter")
		// The target this actor is trying to hit.
		int Target;
	UPROPERTY(EditAnywhere, Category = "Custom Parameter")
		// The collider for this actor.
		class USphereComponent* OurCollider{ nullptr };

	UFUNCTION()
		// Function for when this actors collider overlaps with 
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* Othercomponent,
			int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
