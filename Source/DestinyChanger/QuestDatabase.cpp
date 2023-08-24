// Fill out your copyright notice in the Description page of Project Settings.


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
