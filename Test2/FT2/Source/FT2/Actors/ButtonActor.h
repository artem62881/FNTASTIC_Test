// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "ButtonActor.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleased);

UCLASS(Blueprintable)
class FT2_API AButtonActor : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AButtonActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UArrowComponent* PreviewArrow;
	
	void PressButton();

	void ReleaseButton();
	
	FOnButtonPressed OnButtonPressed;
	FOnButtonReleased OnButtonReleased;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnVolumeEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnButtonPressedEvent();

	UFUNCTION(BlueprintNativeEvent)
	void OnButtonReleasedEvent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PressingDepth = 10.f;
	
private:
	bool bIsBlocked = false;

};