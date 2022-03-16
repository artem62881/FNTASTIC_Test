// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"
#include "Components/ShapeComponent.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	checkf(IsValid(InteractionVolume), TEXT("AInteractiveActor::BeginPlay() Interaction volume has to be set in all child classes"));
	InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveActor::OnVolumeBeginOverlapEvent);
	InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &AInteractiveActor::OnVolumeEndOverlapEvent);
}

void AInteractiveActor::OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AInteractiveActor::OnVolumeEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
