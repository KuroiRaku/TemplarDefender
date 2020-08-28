// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"
#include "MainCharacterAngel.h"
#include "MainCharacterDemon.h"
#include "MainCharacterKnight.h"

/**
 * 
 */
UCLASS()
class TEMPLARDEFENDER_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AMainCharacterKnight* Knight;
	AMainCharacterDemon* Demon;
	AMainCharacterAngel* Angel;

	

public:
	enum {
		Knight = 1, Demon = 2, Angel =3
	};

	AMainLevelScriptActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
