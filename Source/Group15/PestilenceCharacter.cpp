// Fill out your copyright notice in the Description page of Project Settings.


#include "PestilenceCharacter.h"

// Sets default values
APestilenceCharacter::APestilenceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Creates a SpringArm Component to move the camera.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	// Sets a lot of parameters for this component.
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, -60.f));
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 315.f, 0.f));
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
void APestilenceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APestilenceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APestilenceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

