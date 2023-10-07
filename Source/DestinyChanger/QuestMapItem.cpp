//制作日：2023/08/26　制作者：トウ　更新内容：マップ上のアイテムのクラス
//制作日：2023/10/5 　制作者：トウ　更新内容：クエストをプレイヤーに与える処理を追加
//制作日：2023/10/5 　制作者：トウ　更新内容：関連するアクターを生成の処理を追加


#include "QuestMapItem.h"
#include "QuestGiverComponent.h"
#include "DialogueManager.h"

#include "MinimapPlugin/Public/MapIconComponent.h"	//Plugin

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
	//関連するアクターをActiveする
	ActiveTargetActor();

	if (QuestGiverComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("QuestGiverComponent is nullptr"));
		return;
	}

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

/**
* @brief Actor を指定された value で隠したり表示したりします。
*
* @details true を指定すると隠され、false を指定すると表示されます。
*
* @param bool _isHidden 隠す/表示するかを指定する bool 値です。
*/
void AQuestMapItem::SetActorDeepHidden_Implementation(bool _isHidden)
{
	SetActorHiddenInGame(_isHidden);
	SetActorEnableCollision(!_isHidden);
	SetActorTickEnabled(!_isHidden);

	//Get Component MapIcon
	UMapIconComponent* MapIconComponent = Cast<UMapIconComponent>(GetComponentByClass(UMapIconComponent::StaticClass()));
	if (MapIconComponent != nullptr) {
		MapIconComponent->SetIconVisible(!_isHidden);
	}
}

