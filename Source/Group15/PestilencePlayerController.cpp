// Fill out your copyright notice in the Description page of Project Settings.


#include "PestilencePlayerController.h"


void APestilencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* myHud = CreateWidget(this, PestilenceHud_WBP);

	if (myHud != nullptr)
	{
		myHud->AddToViewport();
	}
}