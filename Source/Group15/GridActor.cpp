// Fill out your copyright notice in the Description page of Project Settings.



#include "GridActor.h"
#include "GenericEnemyCharacter.h"
#include "Containers/UnrealString.h"

// Sets default values
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Offsets the location of the HitBoxGrid.
	GridOffsetX = 2800;
	GridOffsetY = -200.f;

	// The colors of the hitboxes when they hit or miss objects.
	MissColor = FLinearColor(0.f, 255.f, 0.f, 0.f);
	HitColor = FLinearColor(255.f, 30.f, 0.f, 0.8f);

	EnableDrawDebug = false;
	UELogWarnings = false;

	
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	// GridSize
	const int XSize = 99;
	const int YSize = 49;

	// Setting the size of the grid that holds info on each cell.
	TArray<int> TempArray;
	TempArray.Init(0, XSize);
	IntGridArray.Init(TempArray, YSize);

	BoxTracing();
	SpawnEnemies();
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnableDrawDebug)
	{
		AGridActor::BoxTracing();
	}
}

void AGridActor::SpawnEnemies()
{
	if (EnableEnemySpawn)
	{
		for (int i = 0; i < Data.Num(); i++)
		{
			FActorSpawnParameters SpawnInfo;	//  Defining default SpawnParamenters
			SpawnInfo.Name = Data[i].EnemyName;	// Sets ID Name.
			if (Data.IsValidIndex(i) && IsValid(GenericEnemy_BP))
			{
				if (GetGridCell(
					(Data[i].EnemyLocation.GetLocation().X - GetActorLocation().X) / 100,
					(Data[i].EnemyLocation.GetLocation().Y - GetActorLocation().Y) / 100) == 1)
				{
					GenericEnemy = GetWorld()->SpawnActor<AGenericEnemyCharacter>(GenericEnemy_BP.Get(), Data[i].EnemyLocation, SpawnInfo);	// Spawns the character.
					GenericEnemy->GridActor = this;	// Gives the character a reference to the grid
					GenericEnemy->XGridReference = (GenericEnemy->GetActorLocation().X - GetActorLocation().X) / 100;
					GenericEnemy->YGridReference = (GenericEnemy->GetActorLocation().Y - GetActorLocation().Y) / 100;
					GenericEnemy->DirFacedOnSpawn = Data[i].FacingDirection;	// Lets the character know which direction it should face.
					GenericEnemy->IsIdle = true;	// Activates the character.
				}
			}
		}
	}
}

void AGridActor::BoxTracing()
{
	// Code Reference (maybe idk)
	// Unreal Engine 4 C++ Tutorial: Sweep Multi Line Trace | https://www.youtube.com/watch?v=Gu5f3-hFFfY

	FHitResult OutHit;
	TArray<AActor*> none;

	// Initializing the HitBoxGrid and Size.
	const int XSize = 99;
	const int YSize = 49;
	FVector gridArray[YSize][XSize];

	for (int y = 0; y < YSize; y++)
	{
		for (int x = 0; x < XSize; x++)
		{
			// Traces boxes in the scene to figure out if cells are occupied by preplaced meshes (Houses, props, etc.).
			gridArray[y][x] = FVector(((-100.f * floor(XSize / 2)) + (100.f * x) + GridOffsetX), ((-100.f * floor(YSize / 2)) + (100.f * y) + GridOffsetY), 25.f);

			bool HitFound = UKismetSystemLibrary::BoxTraceSingle(
				GetWorld(),										// The current world.
				gridArray[y][x],								// Where to start tracing the box from.
				gridArray[y][x] + FVector(0.f, 0.f, 100.f),		// Where to trace the box to.
				FVector(40.f, 40.f, 0.f),						// Size of box (Halfsize(Starts from center, radius)).
				FRotator(0.f, 0.f, 0.f),						// The rotation of the top and bottom sides.
				ETraceTypeQuery::TraceTypeQuery1,				// Custom tracing types.
				false,											// Trace complex.
				none,											// Actors to ignore.
				EDrawDebugTrace::ForOneFrame,					// How long the draw debug should last.
				OutHit,											// Reference to the object hit.
				true,											// Ignore self?
				MissColor,										// DrawDebug color if nothing hits.
				HitColor, 5.f);									// DrawDebug color if a hit is made.

			if (HitFound)
			{
				// Set cell as blocked. Cannot be navigated to by anyone.
				IntGridArray[y][x] = 2;

			}
			else
			{
				// Set cell as open.
				IntGridArray[y][x] = 1;
			}
		}
	}
}

int AGridActor::GetGridCell(int x, int y)
{
	// Returns the status of the selected cell.
	if (IntGridArray.IsValidIndex(y) && IntGridArray[y].IsValidIndex(x))
	{
		return IntGridArray[y][x];
	}
	else
	{
		if (UELogWarnings)
			UE_LOG(LogTemp, Warning, TEXT("Something is trying to path to a cell that doesn't exist!"));
		return 0;
	}
	
}

void AGridActor::SetGridCell(int x, int y, int Type)
{
	// Sets a new status to the selected cell.
	IntGridArray[y][x] = Type;
	if (UELogWarnings)
		UE_LOG(LogTemp, Warning, TEXT("GridType is %d"), IntGridArray[y][x]);
}


