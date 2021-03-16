// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyActorGrid.generated.h"

UCLASS()
class GROUP15_API AMyActorGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorGrid();

	UPROPERTY(EditAnywhere, Category = "Location")
	bool EnableDrawDebug;

	UPROPERTY(EditAnywhere, Category = "Location")
	float GridOffsetX;

	UPROPERTY(EditAnywhere, Category = "Location")
	float GridOffsetY;

	UPROPERTY(EditAnywhere, Category = "Location")
	FLinearColor MissColor;
	UPROPERTY(EditAnywhere, Category = "Location")
	FLinearColor HitColor;

	int GridArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

};
