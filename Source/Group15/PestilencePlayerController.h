// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PestilencePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class GROUP15_API APestilencePlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UUserWidget> PestilenceHud_WBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
