// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"
#include "GridActor.generated.h"

class AGenericEnemyCharacter;

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		// X and Y should be in the hundreds for placement to center in cells. Z by default is 90;
		FTransform EnemyLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		FName EnemyName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		int EnemyType = 5;	


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		// The Direction to face. 1=North, 2=East, 3=South, 4=West.
		int FacingDirection;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		// Spawn this Enemy?
		bool SpawnEnemy;
};

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
	UPROPERTY(EditAnywhere, Category = "Location")
		AGenericEnemyCharacter* GenericEnemy;
	UPROPERTY(EditAnywhere, Category = Players, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AGenericEnemyCharacter> GenericEnemy_BP;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		TArray<FEnemyData> Data;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		// Enable spawning of any enemy?
		bool EnableEnemySpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DeveloperParameter")
		// Display UELog Warnings.
		bool UELogWarnings;

	// Values for IntGridArray: 0=Undefined, 1=Open, 2=Blocked, 3=Pestilence.
	TArray<TArray<int>> IntGridArray;

	// Find out what occupies this grid cell.
	int GetGridCell(int x, int y);
	// Update what occupies this grid cell.
	void SetGridCell(int x, int y, int Type);

	class MyClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Traces boxes that collide with the environment, then decides if those cells the boxes occupies should be open or blocked in the grid.
	void BoxTracing();
	// Spawn all the enemies.
	void SpawnEnemies();
};





