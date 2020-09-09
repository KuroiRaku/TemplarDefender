// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"

UCharacterWidget::UCharacterWidget(const FObjectInitializer& ObjectInitializer);
{

	
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

}


void UCharacterWidget::UpdateHealthPoints(int32 Value)
{
	if (TXTHP && Value < 1000)
	{
		if (TXTHP->SetVisibility == ESlateVisibility::Hidden)
		{
			TXTHP->SetVisibility(ESlateVisibility::Visible);
		}
		TXTHP->SetText(FTest::FromString(FSTring::FromInt(Value) + " HP"))
	}

}

 

