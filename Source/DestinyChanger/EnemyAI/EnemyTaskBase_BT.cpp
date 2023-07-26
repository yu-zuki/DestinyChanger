// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTaskBase_BT.h"
#include "../EnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy_BD.h"

EBTNodeResult::Type UEnemyTaskBase_BT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UEnemyTaskBase_BT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

AEnemyBase* UEnemyTaskBase_BT::GetEnemy(UBehaviorTreeComponent& OwnerComp)
{
	if (EnemyPtr == nullptr) {
		//“G‚ÌŽæ“¾
		EnemyPtr = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
		if (EnemyPtr == nullptr) 	return nullptr;
	}

	return EnemyPtr;
}
