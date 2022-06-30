// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdProjectGameMode.h"
#include "ThirdProjectCharacter.h"
#include "GamePlay/RPGGameState.h"
#include "GamePlay/RPGHUD.h"
#include "GamePlay/RPGPlayerState.h"
#include "UObject/ConstructorHelpers.h"

AThirdProjectGameMode::AThirdProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	GameStateClass = ARPGGameState::StaticClass();

	HUDClass = ARPGHUD::StaticClass();

	PlayerStateClass = ARPGPlayerState::StaticClass();
}
