//������F2023/08/25�@����ҁF�g�E�@�X�V���e�F�N�G�X�g�̃f�[�^�x�[�X�N���X���쐬

#include "QuestDatabase.h"

bool AQuestDatabase::QuestExists(FName QuestID) const
{
	//�N�G�X�gID�����݂��邩�ǂ�����Ԃ�
	return AllQuests.ContainsByPredicate(
		[&](const FQuestStruct& Quest) {
			return Quest.QuestDetail.ID == QuestID;
		}
	);
}

FQuestStruct AQuestDatabase::GetQuest(FName QuestID) const
{
	//�N�G�X�g��Ԃ�
	const FQuestStruct* FoundQuest = AllQuests.FindByPredicate(
		[&](const FQuestStruct& Quest) {
			return Quest.QuestDetail.ID == QuestID;
		}
	);

	return FoundQuest ? *FoundQuest : FQuestStruct();
}
