// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuCameraPawn.h"

// Sets default values
AMainMenuCameraPawn::AMainMenuCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a SpringArm Component to move the camera.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Sets a lot of parameters for this component.
	CameraBoom->TargetArmLength = 215;
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, -60.f));
	CameraBoom->SetRelativeRotation(FRotator(325.f, 10.f, 0.f));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.f;
	CameraBoom->CameraLagMaxTimeStep = 0.002f;
	CameraBoom->CameraLagMaxDistance = 200.f;
	CameraBoom->bDoCollisionTest = false;

	// Creates a Camera Component that is attached to the SpringArm.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Makes us possess this character by default.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMainMenuCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMenuCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainMenuCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

