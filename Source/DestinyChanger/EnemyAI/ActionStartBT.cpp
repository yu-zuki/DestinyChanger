// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStartBT.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyBase.h"
#include "BaseEnemy_BD.h"

EBTNodeResult::Type UActionStartBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//State‚ð@Patrol ‚É•ÏX
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Patrol);

	//Enemy‚Ì‚Æ‚±‚ë‚ðŽ¦‚·UI‚ð‰B‚·
	GetEnemy(OwnerComp)->SetEnemyDirectionIndicatorActive(false);

	return EBTNodeResult::Succeeded;
}