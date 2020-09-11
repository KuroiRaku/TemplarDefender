// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditWidget.h"
#include "SlateOptMacros.h"
#include "MainMenuWidget.h"

#define LINE_TERMINATOR
#define LOCTEXT_NAMESPACE "Credit"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCreditWidget::Construct(const FArguments& InArgs)
{
	FString CreditString = FString(TEXT("Programmer : Le Cherng(KuroiRaku)\n\t Thomas (Anne Omnimous)\nArtist : Bionic Bear, Anne Omnious"));


	const FText CreditText= FText::FromString(CreditString);

	const FText TitleText = LOCTEXT("CREDIT!", "Credit");
	const FText BackText = LOCTEXT("Back", "Back");

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);

	FSlateFontInfo CreditTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	CreditTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = CreditTextStyle;
	TitleTextStyle.Size = 60.f;
	
	ChildSlot
	[

		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
		+ SOverlay::Slot()
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

		+ SVerticalBox::Slot()
		.Padding(ButtonPadding)
		[

			SNew(STextBlock)
			.Font(CreditTextStyle)
			.Text(CreditText)
			.Justification(ETextJustify::Center)

		]
	]]
	;
	
}
FReply SCreditWidget::OnBackClicked() const
{
	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
