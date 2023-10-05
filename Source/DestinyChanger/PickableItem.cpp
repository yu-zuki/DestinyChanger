//������F2023/09/28�@����ҁF�g�E�@�X�V���e�F�v���C���[���E����A�C�e���N���X


#include "PickableItem.h"
#include "DialogueManager.h"
#include "ItemGiverComponent.h"

void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueManager == nullptr) return;

	//��b���I��������Player�ɃA�C�e����n��
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
* @brief Actor ���w�肳�ꂽ value �ŉB������\�������肵�܂��B
* 
* @details true ���w�肷��ƉB����Afalse ���w�肷��ƕ\������܂��B
* 
* @param bool _isHidden �B��/�\�����邩���w�肷�� bool �l�ł��B
*/
void APickableItem::SetActorDeepHidden(bool _isHidden)
{
	SetActorHiddenInGame(_isHidden);
	SetActorEnableCollision(!_isHidden);
	SetActorTickEnabled(!_isHidden);
}
