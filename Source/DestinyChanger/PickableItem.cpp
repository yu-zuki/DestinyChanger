//制作日：2023/09/28　制作者：トウ　更新内容：プレイヤーが拾えるアイテムクラス


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

/**
* @brief Actor を指定された value で隠したり表示したりします。
* 
* @details true を指定すると隠され、false を指定すると表示されます。
* 
* @param bool _isHidden 隠す/表示するかを指定する bool 値です。
*/
void APickableItem::SetActorDeepHidden(bool _isHidden)
{
	SetActorHiddenInGame(_isHidden);
	SetActorEnableCollision(!_isHidden);
	SetActorTickEnabled(!_isHidden);
}
