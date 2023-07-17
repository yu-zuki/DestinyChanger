// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStartBT.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy_BD.h"

EBTNodeResult::Type UActionStartBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//State‚ð@Patrol ‚É•ÏX
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Patrol);

	return EBTNodeResult::Succeeded;
}