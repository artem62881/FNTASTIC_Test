// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NestActor.generated.h"

class AButtonActor;
class AMouseCharacter;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class FT2_API ANestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANestActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMeshComponent* NestMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* SpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UArrowComponent* SpawnArrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* FinishPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FinishMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* FinishVolume;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	AButtonActor* Button;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMouseCharacter> CharacterToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float TrackDistance = 1000.f;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterFinished();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnActivateNestEvent();
	
private:
	UFUNCTION()
	void ActivateNest();
		
	UFUNCTION()
	void OnCharacterDestroyed(AActor* DestroyedActor);
	
	UFUNCTION()
	void OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	TWeakObjectPtr<AMouseCharacter> CurrentlySpawnedCharacter = nullptr;
};
