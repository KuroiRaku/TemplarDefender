// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWidget.h"

UCharacterWidget::UCharacterWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCharacterWidget::UpdateHealthPoints(int32 Value)
{
	TXTHP->SetVisibility(ESlateVisibility::Visible);
	ABaseCharacter player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TXTHP->SetText(player.Health(FSTring::FromInt(Value) + " HP"));

	if (TXTHP && Value < 1000)
	{
		if (TXTHP -> SetVisibility == ESlateVisibility::Hidden)
		{
			TXTHP->SetVisibility(ESlateVisibility::Visible);
		}
		
		/*AMainCharacter m_Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		TXTHP->SetText(m_Player.hp (FSTring::FromInt(Value) + " HP"));*/


		


	}

}

 

