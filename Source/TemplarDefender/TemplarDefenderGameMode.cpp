// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TemplarDefenderGameMode.h"
#include "TemplarDefenderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATemplarDefenderGameMode::ATemplarDefenderGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = ATemplarDefenderCharacter::StaticClass();
	
}
