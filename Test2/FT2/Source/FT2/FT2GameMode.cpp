// Copyright Epic Games, Inc. All Rights Reserved.

#include "FT2GameMode.h"
#include "FT2Character.h"
#include "UObject/ConstructorHelpers.h"

AFT2GameMode::AFT2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
