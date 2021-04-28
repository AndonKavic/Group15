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
	MovementDistance = 100.f;

	// Where this character is located in the Grid.
	XGridReference = 0;
	YGridReference = 0;

	// Developer Parameters.
	UELogWarnings = true;

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

	bIsMoving = false;
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

	GridActor->SetGridCell(XGridReference, YGridReference, 3);	// Sets occupation where Pestilence spawned.



	if (fcurve)
	{
		// Add the float curve to the timeline and connect it to the interpfunctions delegate.
		MyTimeline->AddInterpFloat(fcurve, InterpFunction, FName("Alpha"));
		// Add our on timeline finished function.
		MyTimeline->SetTimelineFinishedFunc(TimelineFinished);

		// Set Vectors.
		

		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(false);
	}


	
	





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
	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &APestilenceCharacter::Esc);
	PlayerInputComponent->BindAction("P", IE_Pressed, this, &APestilenceCharacter::PrintArray);
}

void APestilenceCharacter::TimelineFloatReturn(float value)
{
	bIsMoving = true;
	//SetActorLocation(FMath::Lerp(StartLocation, EndLocation, value));
	AddMovementInput(GetMesh()->GetRightVector(), value);
}

void APestilenceCharacter::OnTimelineFinished()
{
	bIsMoving = false;
}


void APestilenceCharacter::Move(int Direction)
{
	short GetGridResult;
	short XDirection;
	short YDirection;

	switch (Direction)
	{
	case 1:
	{
		XDirection = 1;
		YDirection = 0;
		break;
	}
	case 2:
	{
		XDirection = 0;
		YDirection = 1;
		break;
	}
	case 3:
	{
		XDirection = -1;
		YDirection = 0;
		break;
	}
	case 4:
	{
		XDirection = 0;
		YDirection = -1;
		break;
	}
	default:
		break;
	}

	
	GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f * (Direction - 2), 0.f), false, false, ETeleportType::None);	// Rotates Pestilence.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference + XDirection, YGridReference + YDirection); // Checks what occupies the cell.


		switch (GetGridResult)	// Do something with the result.
		{
		case 0: // Undefined
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that is Undefined!"));
			break;
		}
		case 1:	// Open
		{

			// Block the new cell
			GridActor->SetGridCell(XGridReference + XDirection, YGridReference + YDirection, 2);	// Where Pestilence moved to.






			// Move the character.
			StartLocation = GetActorLocation();
			EndLocation = StartLocation + FVector(MovementDistance * XDirection, MovementDistance * YDirection, 0.f);

			MyTimeline->PlayFromStart();	

			// Correctly update cell types.
			GridActor->SetGridCell(XGridReference + XDirection, YGridReference + YDirection, 3);	// Where Pestilence moved to.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where Pestilence started.

			// Adjust Pestilences location to match the new one.
			XGridReference += XDirection;
			YGridReference += YDirection;
			break;
		}
		case 2:	// Blocked
		{
			// Pathing to cell is blocked.
			break;
		}
		case 3:	// Pestilence
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell it is already occupying!"));
			break;
		}
		case 4:	// Interactive
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a interactive is occupying."));
			break;
		}
		case 5:	// GenericEnemy
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a GenericEnemy is occupying, There shouldn't be any on release btw!"));

			UWorld* World = GetWorld();
			FActorSpawnParameters SpawnInfo;

			if (World && IsValid(InfectedTouch_BP))
				World->SpawnActor<APestilenceOverlapActor>(InfectedTouch_BP.Get(), GetActorLocation() + FVector(100.f * XDirection, 100.f * YDirection, 70.f), GetActorRotation(), SpawnInfo);
			break;
		}
		case 6:	// Peasant
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a Peasant is occupying."));
			break;
		}
		case 7:	// Guard
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a Guard is occupying."));
			break;
		}
		case 8:	// Doctor
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a Doctor is occupying."));
			break;
		}
		case 9:	// Knight
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Pestilence is trying to path to a cell that a Knight is occupying."));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		if (UELogWarnings)
			UE_LOG(LogTemp, Warning, TEXT("Pestilence is missing reference to GridActor"));
	}
}

void APestilenceCharacter::Up()
{
	if(!bIsMoving)
	Move(1);
}

void APestilenceCharacter::Right()
{
	if (!bIsMoving)
	Move(2);
}

void APestilenceCharacter::Down()
{
	if (!bIsMoving)
	Move(3);
}

void APestilenceCharacter::Left()
{
	if (!bIsMoving)
	Move(4);
}

void APestilenceCharacter::Esc()
{	
	FGenericPlatformMisc::RequestExit(true);
}

void APestilenceCharacter::PrintArray()
{
	int x = 0;
	UE_LOG(LogTemp, Warning, TEXT("GridType is %d"), GridActor->IntGridArray[YGridReference][XGridReference]);
	for (int y = 0; y < 49; y++)
	{
		if (y >= 10)
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Cells at row y:%d, is occupied by: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"),
				y, GridActor->GetGridCell(x, y), GridActor->GetGridCell(x + 1, y), GridActor->GetGridCell(x + 2, y), GridActor->GetGridCell(x + 3, y), GridActor->GetGridCell(x + 4, y), GridActor->GetGridCell(x + 5, y), GridActor->GetGridCell(x + 6, y), GridActor->GetGridCell(x + 7, y), GridActor->GetGridCell(x + 8, y), GridActor->GetGridCell(x + 9, y)
				, GridActor->GetGridCell(x + 10, y), GridActor->GetGridCell(x + 11, y), GridActor->GetGridCell(x + 12, y), GridActor->GetGridCell(x + 13, y), GridActor->GetGridCell(x + 14, y), GridActor->GetGridCell(x + 15, y), GridActor->GetGridCell(x + 16, y), GridActor->GetGridCell(x + 17, y), GridActor->GetGridCell(x + 18, y), GridActor->GetGridCell(x + 19, y)
				, GridActor->GetGridCell(x + 20, y), GridActor->GetGridCell(x + 21, y), GridActor->GetGridCell(x + 22, y), GridActor->GetGridCell(x + 23, y), GridActor->GetGridCell(x + 24, y), GridActor->GetGridCell(x + 25, y), GridActor->GetGridCell(x + 26, y), GridActor->GetGridCell(x + 27, y), GridActor->GetGridCell(x + 28, y), GridActor->GetGridCell(x + 29, y)
				, GridActor->GetGridCell(x + 30, y), GridActor->GetGridCell(x + 31, y), GridActor->GetGridCell(x + 32, y), GridActor->GetGridCell(x + 33, y), GridActor->GetGridCell(x + 34, y), GridActor->GetGridCell(x + 35, y), GridActor->GetGridCell(x + 36, y), GridActor->GetGridCell(x + 37, y), GridActor->GetGridCell(x + 38, y), GridActor->GetGridCell(x + 39, y)
				, GridActor->GetGridCell(x + 40, y), GridActor->GetGridCell(x + 41, y), GridActor->GetGridCell(x + 42, y), GridActor->GetGridCell(x + 43, y), GridActor->GetGridCell(x + 44, y), GridActor->GetGridCell(x + 45, y), GridActor->GetGridCell(x + 46, y), GridActor->GetGridCell(x + 47, y), GridActor->GetGridCell(x + 48, y));
		}
		else
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("Cells at row y:0%d, is occupied by: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"),
				y, GridActor->GetGridCell(x, y) , GridActor->GetGridCell(x+1, y), GridActor->GetGridCell(x+2, y), GridActor->GetGridCell(x+3, y), GridActor->GetGridCell(x+4, y), GridActor->GetGridCell(x+5, y), GridActor->GetGridCell(x+6, y), GridActor->GetGridCell(x+7, y), GridActor->GetGridCell(x+8, y), GridActor->GetGridCell(x+9, y)
				, GridActor->GetGridCell(x+10, y), GridActor->GetGridCell(x+11, y), GridActor->GetGridCell(x+12, y), GridActor->GetGridCell(x+13, y), GridActor->GetGridCell(x+14, y), GridActor->GetGridCell(x+15, y), GridActor->GetGridCell(x+16, y), GridActor->GetGridCell(x+17, y), GridActor->GetGridCell(x+18, y), GridActor->GetGridCell(x+19, y)
				, GridActor->GetGridCell(x+20, y), GridActor->GetGridCell(x+21, y), GridActor->GetGridCell(x+22, y), GridActor->GetGridCell(x+23, y), GridActor->GetGridCell(x+24, y), GridActor->GetGridCell(x+25, y), GridActor->GetGridCell(x+26, y), GridActor->GetGridCell(x+27, y), GridActor->GetGridCell(x+28, y), GridActor->GetGridCell(x+29, y)
				, GridActor->GetGridCell(x+30, y), GridActor->GetGridCell(x+31, y), GridActor->GetGridCell(x+32, y), GridActor->GetGridCell(x+33, y), GridActor->GetGridCell(x+34, y), GridActor->GetGridCell(x+35, y), GridActor->GetGridCell(x+36, y), GridActor->GetGridCell(x+37, y), GridActor->GetGridCell(x+38, y), GridActor->GetGridCell(x+39, y)
				, GridActor->GetGridCell(x+40, y), GridActor->GetGridCell(x+41, y), GridActor->GetGridCell(x+42, y), GridActor->GetGridCell(x+43, y), GridActor->GetGridCell(x+44, y), GridActor->GetGridCell(x+45, y), GridActor->GetGridCell(x+46, y), GridActor->GetGridCell(x+47, y), GridActor->GetGridCell(x+48, y));
		}
	}
}
