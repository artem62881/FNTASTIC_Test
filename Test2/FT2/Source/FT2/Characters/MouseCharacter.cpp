// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseCharacter.h"

void AMouseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentMovementType == EMovementType::MovingForward)
	{
		MoveForward();
	}
}

void AMouseCharacter::FinishRace()
{
	CurrentMovementType = EMovementType::Waiting;
	bFinished = true;
	if (OnFinished.IsBound())
	{
		OnFinished.Broadcast();
	}
}

void AMouseCharacter::BeginPlay()
{
	Super::BeginPlay();
	bFinished = false;
}

void AMouseCharacter::MoveForward()
{
	// find out which way is forward
	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
		
	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction);
}

void AMouseCharacter::TurnAround()
{
	const FRotator DeltaRot = FRotator(0.f, 180.f, 0.f);
	AddActorWorldRotation(DeltaRot);
}
