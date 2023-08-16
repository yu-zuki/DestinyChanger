// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem.h"
#include "DestinyChangerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UQuestSystem::UQuestSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ADestinyChangerCharacter* UQuestSystem::GetPlayer()
{
	return Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter( GetWorld(), 0));
}

void UQuestSystem::AddActiveQuest(FName QuestID)
{
	//アクティブのクエストを追加する
	ActiveQuests.Add(QuestID);
}

void UQuestSystem::AddCompletedQuest(FName QuestID)
{
	//完成のクエストを追加する
	CompletedQuests.Add(QuestID);
}

void UQuestSystem::AddExecutingQuest(FName QuestID)
{
	//実行中のクエストを追加する
	ExecutingQuests.Add(QuestID);
}

void UQuestSystem::AddQuestItem(FName ItemID, int32 Num)
{
}

void UQuestSystem::AddDefeatRecord(FName EnemyID, int32 Num)
{
}

