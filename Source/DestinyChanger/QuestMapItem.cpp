//������F2023/08/26�@����ҁF�g�E�@�X�V���e�F�}�b�v��̃A�C�e���̃N���X
//������F2023/10/5 �@����ҁF�g�E�@�X�V���e�F�N�G�X�g���v���C���[�ɗ^���鏈����ǉ�
//������F2023/10/5 �@����ҁF�g�E�@�X�V���e�F�֘A����A�N�^�[�𐶐��̏�����ǉ�


#include "QuestMapItem.h"
#include "QuestGiverComponent.h"
#include "DialogueManager.h"

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
	//�N�G�X�g�Ɏg��Actor���X�|�[������
	SpawnTargetActor();

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

