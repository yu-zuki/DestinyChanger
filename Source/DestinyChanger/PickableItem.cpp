// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "DialogueManager.h"
#include "ItemGiverComponent.h"

void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueManager == nullptr) return;

	//会話が終了したらPlayerにアイテムを渡す
	DialogueManager->AddDialogueFinishedEventCall(this, &APickableItem::PickableQuestItem);
}

APickableItem::APickableItem()
{
	ItemGiverComponent = CreateDefaultSubobject<UItemGiverComponent>(TEXT("ItemGiverComponent"));
}

void APickableItem::PickableQuestItem()
{
	if (ItemGiverComponent == nullptr) return;

	ItemGiverComponent->GiveItemToPlayer();
}
