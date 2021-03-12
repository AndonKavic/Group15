// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PestilenceCharacter.generated.h"

UCLASS()
class GROUP15_API APestilenceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APestilenceCharacter();

	UPROPERTY(EditAnywhere, Category = "MyCamera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, Category = "MyCamera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UCapsuleComponent* MyCapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "CustomParameter")
		float MovementDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void Up();
	void Down();
	void Left();
	void Right();

};
