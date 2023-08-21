// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue_UMG.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UDialogue_UMG : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* Canvas;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* SpeakerName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* DialogueText;

	//”wŒi–ÍŒÐ
	UPROPERTY(Meta = (BindWidget))
		class UBackgroundBlur* Blur;



	//Set SpeakerName
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetSpeakerName(FText Name);

	//Set DialogueText
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetDialogueText(FText Text);
	
};
