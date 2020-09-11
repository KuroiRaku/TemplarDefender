// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHud.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLARDEFENDER_API AMenuHud : public AHUD
{
	GENERATED_BODY()
	
public:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay()override;

	void ShowMenu();

	void RemoveMenu();
};
