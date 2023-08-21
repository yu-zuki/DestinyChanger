// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue_UMG.h"
#include "Components/TextBlock.h"

void UDialogue_UMG::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDialogue_UMG::SetSpeakerName(FText Name)
{
	SpeakerName->SetText(Name);
}

void UDialogue_UMG::SetDialogueText(FText Text)
{
	DialogueText->SetText(Text);
}
