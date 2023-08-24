//制作日：2023/08/16　制作者：トウ　更新内容：クエストが必要な構造体を作成
//制作日：2023/08/25　制作者：トウ　更新内容：クエストが必要な関数を作成
//制作日：2023/08/25　制作者：トウ　更新内容：クエストのUIに関する関数を作成


#include "QuestSystem.h"
#include "DestinyChangerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChangerGameMode.h"
#include "QuestDatabase.h"


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

ADestinyChangerGameMode* UQuestSystem::GetGameMode()
{
	if (GetWorld() == nullptr) return nullptr;

	if (GameMode == nullptr) {
		GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
		return GameMode;
	}

	return GameMode->IsValidLowLevel() ? GameMode : GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());

}

void UQuestSystem::AddActiveQuest(FName QuestID)
{
	//QuestDatabaseからクエストが存在するか確認する
	if( !GameMode->GetQuestDatabase()->QuestExists(QuestID) ) return;

	//アクティブのクエストを追加する
	ActiveQuests.Add(QuestID);

	//実行中のクエストに追加する
	AddExecutingQuest(QuestID);
}

void UQuestSystem::AddCompletedQuest(FName QuestID)
{
	//完成のクエストを追加する
	CompletedQuests.Add(QuestID);

	//アクティブのクエストから削除する
	ActiveQuests.Remove(QuestID);

	//実行中のクエストから削除する
	ExecutingQuests.Remove(QuestID);
}

void UQuestSystem::AddExecutingQuest(FName QuestID)
{
	//実行中のクエストを追加する
	ExecutingQuests.Add(QuestID);

	//実行中のクエストを追加したことを通知する
	UINotifyExecutingQuest.ExecuteIfBound(QuestID);

}

void UQuestSystem::AddQuestItem(FName ItemID, int32 Num)
{
}

void UQuestSystem::AddDefeatRecord(FName EnemyID, int32 Num)
{
}

TArray<FQuestStruct> UQuestSystem::GetActiveQuests()
{	
	//QuestDatabaseからアクティブクエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ActiveQuests) {
		Quests.Add(GameMode->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetCompletedQuests()
{
	//QuestDatabaseから完成クエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : CompletedQuests) {
		Quests.Add(GameMode->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetExecutingQuests()
{
	//QuestDatabaseから実行中クエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ExecutingQuests) {
		Quests.Add(GameMode->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

int32 UQuestSystem::GetQuestItems(FName ItemID)
{
	//QuestItems からアイテムの数を取得する
	return QuestItems.FindRef(ItemID);
}

int32 UQuestSystem::GetDefeatRecords(FName ItemID)
{
	//DefeatRecords から敵の数を取得する
	return DefeatRecords.FindRef(ItemID);
}

