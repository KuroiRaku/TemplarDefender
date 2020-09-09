// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

/**
 * 
 */
UCLASS()
class TEMPLARDEFENDER_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCharacterWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	void UpdateHealthPoints(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget));
	class UTextBlock* TXTHP;
	
};
