// Copyright Epic Games, Inc. All Rights Reserved.

#include "DestinyChangerGameMode.h"
#include "DestinyChangerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADestinyChangerGameMode::ADestinyChangerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
