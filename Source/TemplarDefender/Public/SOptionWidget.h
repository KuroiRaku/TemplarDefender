// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class TEMPLARDEFENDER_API SOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SOptionWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHud>, OwningHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//FReply OnPlayClicked() const;
	FReply OnBackClicked() const;
};
