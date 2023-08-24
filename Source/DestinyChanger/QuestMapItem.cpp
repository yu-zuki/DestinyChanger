// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMapItem.h"
#include "QuestGiverComponent.h"
#include "DialogueManager.h"

AQuestMapItem::AQuestMapItem()
{
	QuestGiverComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));
}

void AQuestMapItem::GiveQuestToPlayer()
{
	QuestGiverComponent->GiveQuestToPlayer();
}

void AQuestMapItem::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueManager == nullptr) return;

	DialogueManager->AddDialogueFinishedEventCall(this,&AQuestMapItem::GiveQuestToPlayer);
}

