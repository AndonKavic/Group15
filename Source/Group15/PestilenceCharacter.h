// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GridActor.h"
#include "PestilenceOverlapActor.h"
#include "PestilenceCharacter.generated.h"

UCLASS()
class GROUP15_API APestilenceCharacter : public ACharacter
{
	GENERATED_BODY()

		class UTimelineComponent* MyTimeline;
		 
public:
	// Sets default values for this character's properties
	APestilenceCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		AGridActor* GridActor;
	UPROPERTY(EditAnywhere, Category = "Grid")
		int XGridReference;
	UPROPERTY(EditAnywhere, Category = "Grid")
		int YGridReference;

	UPROPERTY(EditAnywhere, Category = "Actions")
		TSubclassOf<class APestilenceOverlapActor> InfectedTouch_BP;

	UPROPERTY(EditAnywhere, Category = "MyCamera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, Category = "MyCamera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "CustomParameter")
		// How far this character moves.
		float MovementDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DeveloperParameter")
		// Display UELog Warnings.
		bool UELogWarnings;


	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* fcurve;



	UPROPERTY(EditAnywhere, Category = "Timeline")
		float ZOffset;

	FOnTimelineFloat InterpFunction{};


	FOnTimelineEvent TimelineFinished{};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


	UFUNCTION()
		void TimelineFloatReturn(float value);

	UFUNCTION()
		void OnTimelineFinished();

	UPROPERTY()
		FVector StartLocation;

	UPROPERTY()
		FVector EndLocation;

	bool bIsMoving;

	void Move(int Direction);
	void Up();
	void Down();
	void Left();
	void Right();
	void Esc();
	// Prints the values of the whole array as a ULog Warning.
	void PrintArray();
};
