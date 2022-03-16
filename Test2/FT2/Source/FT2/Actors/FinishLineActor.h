// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "FinishLineActor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FT2_API AFinishLineActor : public AInteractiveActor
{
	GENERATED_BODY()

public:
	AFinishLineActor();

protected:
	UFUNCTION()
	virtual void OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};

