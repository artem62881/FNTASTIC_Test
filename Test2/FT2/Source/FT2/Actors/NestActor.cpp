// Fill out your copyright notice in the Description page of Project Settings.


#include "NestActor.h"
#include "ButtonActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "FT2/Characters/MouseCharacter.h"

// Sets default values
ANestActor::ANestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	NestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NestMesh"));
	NestMesh->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(NestMesh);
	
	SpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPreviewArrow"));
	SpawnArrow->SetupAttachment(SpawnPoint);

	FinishPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FinishPoint"));
	FinishPoint->SetupAttachment(SpawnPoint);

	FinishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FinishMesh"));
	FinishMesh->SetupAttachment(FinishPoint);

	FinishVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("FinishVolume"));
	FinishVolume->SetupAttachment(FinishPoint);
}

// Called when the game starts or when spawned
void ANestActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Button))
	{
		FinishVolume->OnComponentBeginOverlap.AddDynamic(this, &ANestActor::OnVolumeBeginOverlapEvent);
		Button->OnButtonPressed.AddDynamic(this, &ANestActor::ActivateNest);
	}
}

void ANestActor::OnConstruction(const FTransform& Transform)
{
	FinishPoint->SetRelativeLocation(-SpawnPoint->GetRightVector() * TrackDistance);
}

void ANestActor::OnCharacterDestroyed(AActor* DestroyedActor)
{
	if (IsValid(Button) && CurrentlySpawnedCharacter == DestroyedActor)
	{
		CurrentlySpawnedCharacter = nullptr;
		Button->ReleaseButton();
	}
}

void ANestActor::ActivateNest()
{
	if (IsValid(CharacterToSpawn))
	{
		CurrentlySpawnedCharacter = GetWorld()->SpawnActor<AMouseCharacter>(CharacterToSpawn, SpawnPoint->GetComponentTransform());
	}
	
	if (CurrentlySpawnedCharacter.IsValid())
	{
		CurrentlySpawnedCharacter->OnFinished.AddDynamic(this, &ANestActor::OnCharacterFinished);
		CurrentlySpawnedCharacter->OnDestroyed.AddDynamic(this, &ANestActor::OnCharacterDestroyed);
		OnActivateNestEvent();
	}
}

void ANestActor::OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AMouseCharacter>())
	{
		AMouseCharacter* Character = StaticCast<AMouseCharacter*>(OtherActor);
		Character->FinishRace();
	}
}
