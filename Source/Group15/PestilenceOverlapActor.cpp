// Fill out your copyright notice in the Description page of Project Settings.


#include "PestilenceOverlapActor.h"

// Sets default values
APestilenceOverlapActor::APestilenceOverlapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our Collider.
	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;

	Target = 5;	// Default Target
	OurCollider->SetGenerateOverlapEvents(true);	// Enables Overlap Events.
}

// Called when the game starts or when spawned
void APestilenceOverlapActor::BeginPlay()
{
	Super::BeginPlay();

	// Connecting the Overlap-event from the engine to a function in this object.
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &APestilenceOverlapActor::OnOverlap);
	
}

// Called every frame
void APestilenceOverlapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APestilenceOverlapActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* Othercomponent,
	int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Pestilence targets %s"), *OtherActor->GetName());

	switch (Target)
	{
	case 5:
	{
		if (OtherActor->IsA(AGenericEnemyCharacter::StaticClass()))
		{
			Cast<AGenericEnemyCharacter>(OtherActor)->Infection();
			
		}
		else
		{
			//Error
		}
		break;
	}
	default:
		break;
	}
	this->Destroy();
}