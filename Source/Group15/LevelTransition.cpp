// Fill out your copyright notice in the Description page of Project Settings.
// Code taken from Harrison McGuire | Source: https://github.com/Harrison1/unrealcpp/tree/master/TriggerBox

#include "LevelTransition.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

ALevelTransition::ALevelTransition()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &ALevelTransition::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALevelTransition::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, 999, 0, 5);
}

void ALevelTransition::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && OtherActor != this)
    {
        OtherActor->IsA(APestilenceCharacter::StaticClass());
        UGameplayStatics::OpenLevel(GetWorld(), "Level_2");
       
    }
}