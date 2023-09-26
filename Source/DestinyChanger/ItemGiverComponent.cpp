// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemGiverComponent.h"
#include "DestinyChangerCharacter.h"
#include "QuestSystem.h"
#include "Kismet/GameplayStatics.h"
#include "InteractComponent.h"

// Sets default values for this component's properties
UItemGiverComponent::UItemGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemGiverComponent::GiveItemToPlayer()
{ 
	//ItemID Check
	if (ItemID.IsEmpty())	{
	return;
	}

	//GetPlayer
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player == nullptr) return;

	//Find QuestSystem
	UQuestSystem* QuestSystem = Player->FindComponentByClass<UQuestSystem>();
	if (QuestSystem == nullptr) return;

	//Give Item
	for (const auto&Item : ItemID){
		QuestSystem->AddQuestItem(Item.Key,ItemID[Item.Key]);
	}


	UInteractComponent* InteractComponent = Player->FindComponentByClass<UInteractComponent>();
	if (InteractComponent == nullptr) return;

	//UI Off
	InteractComponent->SetUIActive(false);
	InteractComponent->SetInteractObject(nullptr);

	//Destroy Actor
	GetOwner()->Destroy();
}
