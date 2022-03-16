// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLineActor.h"
#include "Components/BoxComponent.h"
#include "FT2/Characters/MouseCharacter.h"

AFinishLineActor::AFinishLineActor()
{
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionVolume->SetupAttachment(Mesh);
}

void AFinishLineActor::OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnVolumeBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,SweepResult);
	if (OtherActor->IsA<AMouseCharacter>())
	{
		AMouseCharacter* Character = StaticCast<AMouseCharacter*>(OtherActor);
		Character->FinishRace();
	}
}
