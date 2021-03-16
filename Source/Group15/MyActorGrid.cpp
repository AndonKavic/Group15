// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorGrid.h"

// Sets default values
AMyActorGrid::AMyActorGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridOffsetX = -50.f;
	GridOffsetY = -50.f;

	MissColor = FLinearColor(0.f, 255.f, 0.f, 0.f);
	HitColor = FLinearColor(255.f, 30.f, 0.f, 0.8f);

	EnableDrawDebug = true;
}

// Called when the game starts or when spawned
void AMyActorGrid::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AMyActorGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Code Reference (maybe idk)
	// Unreal Engine 4 C++ Tutorial: Sweep Multi Line Trace | https://www.youtube.com/watch?v=Gu5f3-hFFfY

	FHitResult OutHit;
	TArray<AActor*> none;

	FVector gridArray[49][49];
	if (EnableDrawDebug)
	{
		for (int y = 0; y < 49; y++)
		{
			for (int x = 0; x < 49; x++)
			{

				gridArray[y][x] = FVector(((-100.f * 24) + (100.f * x) + GridOffsetX), ((-100.f * 24) + (100.f * y) + GridOffsetY), 25.f);

				bool HitFound = UKismetSystemLibrary::BoxTraceSingle(
					GetWorld(),										// The current world.
					gridArray[y][x],								// Where to start tracing the box from.
					gridArray[y][x] + FVector(0.f, 0.f, 100.f),		// Where to trace the box to.
					FVector(40.f, 40.f, 0.f),						// Size of box (Halfsize(Starts from center, radius)).
					FRotator(0.f, 0.f, 0.f),							// The rotation of the top and bottom sides.
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
					// Add cells as blocked. Cannot be navigated to by anyone
				}
			}
		}
	}

}

