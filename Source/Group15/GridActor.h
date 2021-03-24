// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"
#include "GridActor.generated.h"

UCLASS()
class GROUP15_API AGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridActor();

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

	// Values for IntGridArray: 0=Undefined, 1=Open, 2=Blocked, 3=Pestilence.
	TArray<TArray<int>> IntGridArray;

	int GetGridCell(int x, int y);
	void SetGridCell(int x, int y, int Type);

	class MyClass;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BoxTracing();
};


