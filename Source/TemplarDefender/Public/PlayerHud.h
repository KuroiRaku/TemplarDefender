// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */


UCLASS()
class TEMPLARDEFENDER_API APlayerHud : public AHUD
{
	GENERATED_BODY()
	
public: 
	APlayerHud();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateHPCount(int32 value);


	
	UFUNCTION()
		void ResetHP();
		
		
		
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUSerWidget> CharacterWidgetClass;

private:
	UComboWidget* CharacterWidget;

};
