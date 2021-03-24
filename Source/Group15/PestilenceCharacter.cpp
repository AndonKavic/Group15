// Fill out your copyright notice in the Description page of Project Settings.


#include "PestilenceCharacter.h"


// Sets default values
APestilenceCharacter::APestilenceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a SpringArm Component to move the camera.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());

	// Sets a lot of parameters for this component.
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, -60.f));
	CameraBoom->SetRelativeRotation(FRotator(315.f, 0.f, 0.f));
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

	// How far the character moves per instance of movement.
	MovementDistance = 4.f;

	// Where this character is located in the Grid.
	XGridReference = 0;
	YGridReference = 0;
}

// Called when the game starts or when spawned
void APestilenceCharacter::BeginPlay()
{
	Super::BeginPlay();	

	// Source: https://answers.unrealengine.com/questions/405325/is-my-use-of-tactoriterator-and-tarray-correct.html
	// Finds the GridActorBP in the world outliner.
	for (TActorIterator<AGridActor> CharacterItr(GetWorld()); CharacterItr; ++CharacterItr)
	{
		GridActor = *CharacterItr;
	}

	// Gets a referrence to this characters location in the grid related to where the GridActor in the scene is placed. (GridActor must be placed on the first cell.)
	XGridReference = (GetActorLocation().X - GridActor->GetActorLocation().X) / 100;
	YGridReference = (GetActorLocation().Y - GridActor->GetActorLocation().Y) / 100;
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
	// Movement Inputs.
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &APestilenceCharacter::Up);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &APestilenceCharacter::Down);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &APestilenceCharacter::Left);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &APestilenceCharacter::Right);
}

void APestilenceCharacter::Up()
{
	short GetGridResult;

	GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f), false, false, ETeleportType::None);	// Rotates the character.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference + 1, YGridReference); // Checks what occupies the cell.

		switch (GetGridResult)	// Do something with the result.
		{
		case 0: // Undefined
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that is Undefined!"));
			break;
		}
		case 1:	// Open
		{
			// Move the character.
			SetActorLocation(GetActorLocation() + FVector(25.f * MovementDistance, 0.f, 0.f));			
			
			// Change cell types.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where Pestilence started.
			GridActor->SetGridCell(XGridReference + 1, YGridReference, 3);	// Where Pestilence moved to.
			XGridReference++;	// Adjust Pestilences location to match the new one.
			break;
		}
		case 2:	// Blocked
		{
			// Pathing to cell is blocked.
			break;
		}
		case 3:	// Pestilence
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell it is already occupying!"));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pestilence is missing reference to GridActor"));
	}
}

void APestilenceCharacter::Down()
{
	short GetGridResult;

	GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f), false, false, ETeleportType::None);	// Rotates the character.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference - 1, YGridReference); // Checks what occupies the cell.

		switch (GetGridResult)	// Do something with the result.
		{
		case 0:	// Undefined
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that is Undefined!"));
			break;
		}
		case 1:	// Open
		{
			// Move the character.
			SetActorLocation(GetActorLocation() + FVector(-25.f * MovementDistance, 0.f, 0.f));			

			// Change cell types.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where Pestilence started.
			GridActor->SetGridCell(XGridReference - 1, YGridReference, 3);	// Where Pestilence moved to.
			XGridReference--;	// Adjust Pestilences location to match the new one.
			break;
		}
		case 2:	// Blocked
		{
			// Pathing to cell is blocked.
			break;
		}
		case 3:	// Pestilence
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell it is already occupying!"));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pestilence is missing reference to GridActor"));
	}
}

void APestilenceCharacter::Left()
{
	short GetGridResult;

	GetMesh()->SetRelativeRotation(FRotator(0.f, 180.f, 0.f), false, false, ETeleportType::None);	// Rotates the character.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference, YGridReference - 1); // Checks what occupies the cell.

		switch (GetGridResult)	// Do something with the result.
		{
		case 0:	// Undefined
		{
			// Display Warning here. Cell is undefined.
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that is Undefined!"));
			break;
		}
		case 1:	// Open
		{
			// Move the character.
			SetActorLocation(GetActorLocation() + FVector(0.f, -25.f * MovementDistance, 0.f));			

			// Change cell types.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where Pestilence started.
			GridActor->SetGridCell(XGridReference, YGridReference - 1, 3);	// Where Pestilence moved to.
			YGridReference--;	// Adjust Pestilences location to match the new one.
			break;
		}
		case 2:	// Blocked
		{
			// Pathing to cell is blocked.
			break;
		}
		case 3:	// Pestilence
		{
			// Display warning here. Pestilence is trying to path to a cell it is already occupying!
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell it is already occupying!"));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pestilence is missing reference to GridActor"));
	}
}

void APestilenceCharacter::Right()
{
	short GetGridResult;

	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f), false, false, ETeleportType::None);	// Rotates the character.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference, YGridReference + 1); // Checks what occupies the cell.

		switch (GetGridResult)	// Do something with the result.
		{
		case 0:	// Undefined
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that is Undefined!"));
			break;
		}
		case 1:	// Open
		{
			// Move the character.
			SetActorLocation(GetActorLocation() + FVector(0.f, 25.f * MovementDistance, 0.f));			

			// Change cell types.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where Pestilence started.
			GridActor->SetGridCell(XGridReference, YGridReference + 1, 3);	// Where Pestilence moved to.
			YGridReference++;	// Adjust Pestilences location to match the new one.
			break;
		}
		case 2:	// Blocked
		{
			// Pathing to cell is blocked.
			break;
		}
		case 3:	// Pestilence
		{
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell it is already occupying!"));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pestilence is missing reference to GridActor"));
	}
}
