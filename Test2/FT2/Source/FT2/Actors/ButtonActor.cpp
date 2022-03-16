// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonActor.h"
#include "Components/SphereComponent.h"
#include "../Characters/PlayerCharacter.h"
#include "Components/ArrowComponent.h"

AButtonActor::AButtonActor()
{
	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(RootComponent);
	
	PreviewArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PreviewArrow"));
	PreviewArrow->SetupAttachment(RootComponent);
}

void AButtonActor::PressButton()
{
	if (bIsBlocked) return;
	
	bIsBlocked = true;
	if (OnButtonPressed.IsBound())
	{
		OnButtonPressed.Broadcast();
	}

	FVector NewMeshLocation = Mesh->GetRelativeLocation() + -Mesh->GetForwardVector() * PressingDepth;
	Mesh->SetRelativeLocation(NewMeshLocation);
}

void AButtonActor::ReleaseButton()
{
	bIsBlocked = false;
	if (OnButtonReleased.IsBound())
	{
		OnButtonReleased.Broadcast();
	}
	
	FVector NewMeshLocation = Mesh->GetRelativeLocation() + Mesh->GetForwardVector() * PressingDepth;
	Mesh->SetRelativeLocation(NewMeshLocation);
}

void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	OnButtonPressed.AddDynamic(this, &AButtonActor::OnButtonPressedEvent);
	OnButtonReleased.AddDynamic(this, &AButtonActor::OnButtonReleasedEvent);
}

void AButtonActor::OnVolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnVolumeBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,SweepResult);
	if (OtherActor->IsA<APlayerCharacter>())
	{
		APlayerCharacter* Character = StaticCast<APlayerCharacter*>(OtherActor);
		Character->RegisterInteractiveActor(this);
	}
}

void AButtonActor::OnVolumeEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnVolumeEndOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (OtherActor->IsA<APlayerCharacter>())
	{
		APlayerCharacter* Character = StaticCast<APlayerCharacter*>(OtherActor);
		Character->UnRegisterInteractiveActor(this);
	}
}

void AButtonActor::OnButtonPressedEvent_Implementation()
{
}

void AButtonActor::OnButtonReleasedEvent_Implementation()
{
}