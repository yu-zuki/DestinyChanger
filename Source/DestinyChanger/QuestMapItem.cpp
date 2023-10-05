//制作日：2023/08/26　制作者：トウ　更新内容：マップ上のアイテムのクラス
//制作日：2023/10/5 　制作者：トウ　更新内容：クエストをプレイヤーに与える処理を追加
//制作日：2023/10/5 　制作者：トウ　更新内容：関連するアクターを生成の処理を追加


#include "QuestMapItem.h"
#include "QuestGiverComponent.h"
#include "DialogueManager.h"

AQuestMapItem::AQuestMapItem()
{
	QuestGiverComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));
}

/**
* @brief プレイヤーにクエストを与えます。
* 
* @details クエストについての情報をプレイヤーに与えます、関連するアクターを生成します。
* 
* @return なし
*/
void AQuestMapItem::GiveQuestToPlayer()
{
	//クエストに使うActorをスポーンする
	SpawnTargetActor();

	//このメソッドはアクターをDestroyする
	QuestGiverComponent->GiveQuestToPlayer();

}

void AQuestMapItem::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueManager == nullptr) return;

	//会話が終わったの処理をBindする
	DialogueManager->AddDialogueFinishedEventCall(this,&AQuestMapItem::GiveQuestToPlayer);
}

