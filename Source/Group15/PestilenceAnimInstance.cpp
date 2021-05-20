// Fill out your copyright notice in the Description page of Project Settings.


#include "PestilenceAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPestilenceAnimInstance::NativeInitializeAnimation()
{
	if (MyPawn == nullptr)
	{
		MyPawn = TryGetPawnOwner();
	}
}

void UPestilenceAnimInstance::UpdateAnimationProperties()
{
	if (MyPawn == nullptr)
	{
		MyPawn = TryGetPawnOwner();
	}

	if (MyPawn)
	{
		FVector TempSpeed = MyPawn->GetVelocity();
		FVector LateralSpeed = FVector(TempSpeed.X, TempSpeed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
}

void UPestilenceAnimInstance::UpdateRunAnimation()
{
	if (MyPawn == nullptr)
	{
		MyPawn = TryGetPawnOwner();
	}

	if (MyPawn)
	{

		//bIsMoving = Cast<APestilenceCharacter>(MyPawn)->bIsMoving;
		bIsMoving = MyPawn->GetMovementComponent()->IsCrouching();

		if (bIsMoving && MovementSpeed < 1.f)
		{
			MovementSpeed += 0.01f;
		}
		else if (MovementSpeed > 0.f)
		{
			MovementSpeed -= 0.01f;
		}
		
	}
}

