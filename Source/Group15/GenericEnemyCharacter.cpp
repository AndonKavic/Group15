// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericEnemyCharacter.h"
#include "GridActor.h"

// Sets default values
AGenericEnemyCharacter::AGenericEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DirFacedOnSpawn = 2;
	IsIdle = false;
	CharacterName = this->GetName();

	MovementDistance = 4.f;
	EnemyType = 5;
	UELogWarnings = true;
	IsInfected = false;

	InfectedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("InfectedMaterial"));

}

// Called when the game starts or when spawned
void AGenericEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenericEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Idle();
}

// Called to bind functionality to input
void AGenericEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGenericEnemyCharacter::Infection()
{	
	IsInfected = true;
	if (IsValid(InfectedMaterial) && IsInfected)
	{
		GetMesh()->SetMaterial(0, InfectedMaterial);
		UE_LOG(LogTemp, Warning, TEXT("Infection success"));
	}
}

void AGenericEnemyCharacter::Idle()
{

	if (IsIdle && IsValid(GridActor))
	{
		IsIdle = false;
		short int temp = FMath::RandRange(3, 6);

		GridActor->SetGridCell(XGridReference, YGridReference, EnemyType);	// Sets occupation where this character spawned.

		switch (1)
		{
		case 1:
		{
			GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, this, &AGenericEnemyCharacter::Walking, temp, false);
			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{

			break;
		}
		default:
			break;
		}
	}
}

void AGenericEnemyCharacter::Walking()
{
	short int Steps = FMath::RandRange(1, 4);
	short int Direction = FMath::RandRange(1, 4);
	while (Steps != 0)
	{
		AGenericEnemyCharacter::Move(Direction);
		Steps--;
		GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, 1, false, 0);
	}
	IsIdle = true;
}

void AGenericEnemyCharacter::Move(int Direction)
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

	GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f*(Direction-2), 0.f), false, false, ETeleportType::None);	// Rotates the character.

	if (IsValid(GridActor))	// Does the GridActor Exist? If not. Uhoh.
	{
		GetGridResult = GridActor->GetGridCell(XGridReference + XDirection, YGridReference + YDirection); // Checks what occupies the cell.

		switch (GetGridResult)	// Do something with the result.
		{
		case 0: // Undefined
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that is Undefined!"), *CharacterName);
			break;
		}
		case 1:	// Open
		{
			// Move the character.
			SetActorLocation(GetActorLocation() + FVector(25.f * MovementDistance * XDirection, 25.f * MovementDistance * YDirection, 0.f));

			// Change cell types.
			GridActor->SetGridCell(XGridReference, YGridReference, 1);	// Where this Character started.
			GridActor->SetGridCell(XGridReference + XDirection, YGridReference + YDirection, EnemyType);	// Where this Character moved to.
			// Adjust this Characters location to match the new one.
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
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that Pestilence is occupying"), *CharacterName);
			break;
		}
		case 4:	// Interactive
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a interactive is occupying."), *CharacterName);
			break;
		}
		case 5:	// GenericEnemy
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a GenericEnemy is occupying, There shouldn't be any on release!"), *CharacterName);
			break;
		}
		case 6:	// Peasant
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a Peasant is occupying."), *CharacterName);
			break;
		}
		case 7:	// Guard
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a Guard is occupying."), *CharacterName);
			break;
		}
		case 8:	// Doctor
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a Doctor is occupying."), *CharacterName);
			break;
		}
		case 9:	// Knight
		{
			if (UELogWarnings)
				UE_LOG(LogTemp, Warning, TEXT("%s is trying to path to a cell that a Knight is occupying."), *CharacterName);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		if (UELogWarnings)
			UE_LOG(LogTemp, Warning, TEXT("%s is missing reference to GridActor"), *CharacterName);
	}
}