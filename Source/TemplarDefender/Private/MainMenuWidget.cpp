// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "MenuHud.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"
#include "SCreditWidget.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);


	const FText TitleText = LOCTEXT("Templer Defender", "Templer Defender 神殿護衛者");
	const FText PlayText = LOCTEXT("Start", "Start スタート");
	const FText SettingsText = LOCTEXT("Settings", "設定");
	const FText QuitText = LOCTEXT("Quit", "戻る");
	const FText CreditText = LOCTEXT("CREDIT!", "Credit");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	ChildSlot
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)

				//Title Text
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					
					
						SNew(STextBlock)
						.Font(TitleTextStyle)
						.Text(TitleText)
						.Justification(ETextJustify::Center)
					
				]

				//Play Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					//declare new button here
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
					[

						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
				]
				//Credit Button
				+ SVerticalBox::Slot()

				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnCreditClicked)
				[

					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(CreditText)
					.Justification(ETextJustify::Center)
				]
				]

				//Quit Button
				+ SVerticalBox::Slot()
				
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnQuitClicked)
					[

						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]
				]
			]

		];
}

FReply SMainMenuWidget::OnPlayClicked() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnPlay is Clicked")));
	if (OwningHUD.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OwningHud is valid")));
		OwningHUD->RemoveMenu();
	}
	return FReply::Handled();
}


FReply SMainMenuWidget::OnCreditClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu();
	}
	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE