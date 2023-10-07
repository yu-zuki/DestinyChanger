//������F2023/08/26�@����ҁF�g�E�@�X�V���e�F�}�b�v��̃A�C�e���̃N���X
//������F2023/10/5 �@����ҁF�g�E�@�X�V���e�F�N�G�X�g���v���C���[�ɗ^���鏈����ǉ�
//������F2023/10/5 �@����ҁF�g�E�@�X�V���e�F�֘A����A�N�^�[�𐶐��̏�����ǉ�


#include "QuestMapItem.h"
#include "QuestGiverComponent.h"
#include "DialogueManager.h"

#include "MinimapPlugin/Public/MapIconComponent.h"	//Plugin

AQuestMapItem::AQuestMapItem()
{
	QuestGiverComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));
}

/**
* @brief �v���C���[�ɃN�G�X�g��^���܂��B
* 
* @details �N�G�X�g�ɂ��Ă̏����v���C���[�ɗ^���܂��A�֘A����A�N�^�[�𐶐����܂��B
* 
* @return �Ȃ�
*/
void AQuestMapItem::GiveQuestToPlayer()
{
	//�֘A����A�N�^�[��Active����
	ActiveTargetActor();

	if (QuestGiverComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("QuestGiverComponent is nullptr"));
		return;
	}

	//���̃��\�b�h�̓A�N�^�[��Destroy����
	QuestGiverComponent->GiveQuestToPlayer();

}

void AQuestMapItem::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueManager == nullptr) return;

	//��b���I������̏�����Bind����
	DialogueManager->AddDialogueFinishedEventCall(this,&AQuestMapItem::GiveQuestToPlayer);
}

/**
* @brief Actor ���w�肳�ꂽ value �ŉB������\�������肵�܂��B
*
* @details true ���w�肷��ƉB����Afalse ���w�肷��ƕ\������܂��B
*
* @param bool _isHidden �B��/�\�����邩���w�肷�� bool �l�ł��B
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

