//制作日：2023/08/25　制作者：トウ　更新内容：クエストのデータベースクラスを作成

#include "QuestDatabase.h"

bool AQuestDatabase::QuestExists(FName QuestID) const
{
	//クエストIDが存在するかどうかを返す
	return AllQuests.ContainsByPredicate(
		[&](const FQuestStruct& Quest) {
			return Quest.QuestDetail.ID == QuestID;
		}
	);
}

FQuestStruct AQuestDatabase::GetQuest(FName QuestID) const
{
	//クエストを返す
	const FQuestStruct* FoundQuest = AllQuests.FindByPredicate(
		[&](const FQuestStruct& Quest) {
			return Quest.QuestDetail.ID == QuestID;
		}
	);

	return FoundQuest ? *FoundQuest : FQuestStruct();
}
