// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStartBT.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyBase.h"
#include "BaseEnemy_BD.h"

EBTNodeResult::Type UActionStartBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Stateを　Patrol に変更
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Patrol);

	//Enemyのところを示すUIを隠す
	GetEnemy(OwnerComp)->SetEnemyDirectionIndicatorActive(false);

	return EBTNodeResult::Succeeded;
}