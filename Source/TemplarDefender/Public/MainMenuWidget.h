// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SMainMenuWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHud>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	UFUNCTION(BlueprintCallable, Category = "Button", meta = (DisplayName = "OnPlayClicked"))
	FReply OnPlayClicked() const;

	UFUNCTION(BlueprintCallable, Category = "Button", meta = (DisplayName = "OnCreditClicked"))
	FReply OnCreditClicked() const;

	UFUNCTION(BlueprintCallable, Category = "Button", meta = (DisplayName = "OnQuitClicked"))
	FReply OnQuitClicked() const;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Background Image"))
	SImage* Image;

	TWeakObjectPtr<class AMenuHud> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
	
};
