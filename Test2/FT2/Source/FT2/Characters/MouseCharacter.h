// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FT2BaseCharacter.h"
#include "MouseCharacter.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	MovingForward = 0,
	Waiting
};

UCLASS()
class FT2_API AMouseCharacter : public AFT2BaseCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
	void FinishRace();

	UFUNCTION(BlueprintCallable)
	bool HasFinished() const { return bFinished; };
	
	FOnFinished OnFinished;
	
protected:
	virtual void BeginPlay() override;
	
	void MoveForward();

	UFUNCTION(BlueprintCallable)
	void TurnAround();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EMovementType CurrentMovementType = EMovementType::MovingForward;
	
private:
	bool bFinished = false;
};
