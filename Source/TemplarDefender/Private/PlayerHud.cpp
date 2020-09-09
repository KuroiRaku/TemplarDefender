// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

APlayerHud::APlayerHud()
{

}


void APlayerHud::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterWidgetClass)
	{
		CharacterWidget = CreateWidget<UCharacterWidget>(GetWorld(), CharacterWidgetClass);
		if (CharacterWidget)
		{
			CharacterWidget->AddToViewport();
		}
	}
}

void APlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APlayerHUD::UpdateHPCount(int32 Value)
{
	if (CharacterWidget)
	{
		CharacterWidget->UpdateHPCount(Value);
	}
}
void APlayerHUD::ResetHP()
{
	if (CharacterWidget)
	{
		CharacterWidget->ResetHP();
	}
}
