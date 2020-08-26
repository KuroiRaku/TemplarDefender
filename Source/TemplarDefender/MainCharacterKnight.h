// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "MainCharacterKnight.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLARDEFENDER_API AMainCharacterKnight : public AMainCharacter
{
	GENERATED_BODY()

public:
	AMainCharacterKnight();
	virtual void Tick(float DeltaTime) override;

protected:
	void attack();

	
};
