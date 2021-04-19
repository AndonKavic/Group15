// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/StaticMesh.h"
#include "GenericEnemyCharacter.generated.h"

class AGridActor;

UCLASS()
class GROUP15_API AGenericEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenericEnemyCharacter();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		AGridActor* GridActor;
	UPROPERTY(EditAnywhere, Category = "Grid")
		int DirFacedOnSpawn;
	UPROPERTY(EditAnywhere, Category = "Grid")
		int XGridReference;
	UPROPERTY(EditAnywhere, Category = "Grid")
		int YGridReference;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class UMaterialInterface* InfectedMaterial;
	UPROPERTY(EditAnywhere, Category = "CustomParameter")
		// The distance traveled per "Step", 4.f = 1 cell.
		float MovementDistance;
	UPROPERTY(EditAnywhere, Category = "CustomParameter")
		// The unique number identifier the grid uses. 5+ for enemies.
		int EnemyType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomParameter")
		bool IsInfected;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomParameter")
		bool CanWalk;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomParameter")
		bool IsIdle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomParameter")
		bool SeesPestilence;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DeveloperParameter")
		// Display UELog Warnings.
		bool UELogWarnings;
	void Infection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FString CharacterName;
	UFUNCTION()
		void Walking();
	UFUNCTION()
	void Idle();
	void Move(int Direction);
	void Up();
	void Down();
	void Left();
	void Right();
	

	FTimerHandle IdleTimerHandle;
};
