//制作日：2023/09/28　制作者：トウ　更新内容：プレイヤーが拾えるアイテムクラス
//制作日：2023/10/07　制作者：トウ　更新内容：QuestActorInterfaceのAPIを追加、クエストがActiveされた時のみアイテムもActiveするように機能を追加


#include "PickableItem.h"
#include "DialogueManager.h"
#include "ItemGiverComponent.h"

#include "MinimapPlugin/Public/MapIconComponent.h"	//Plugin


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
void APickableItem::SetActorDeepHidden_Implementation(bool _isHidden)
{
	SetActorHiddenInGame(_isHidden);
	SetActorEnableCollision(!_isHidden);
	SetActorTickEnabled(!_isHidden);

	//Get Component MapIcon
	UMapIconComponent* MapIconComponent = Cast<UMapIconComponent>(GetComponentByClass(UMapIconComponent::StaticClass()));
	if (MapIconComponent != nullptr)	{
		MapIconComponent->SetIconVisible(!_isHidden);
	}
}
