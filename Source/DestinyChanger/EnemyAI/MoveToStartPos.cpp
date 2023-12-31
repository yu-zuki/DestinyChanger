// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToStartPos.h"
#include "../EnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy_BD.h"

UMoveToStartPos::UMoveToStartPos()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveToStartPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Enemyを取得
	AEnemyBase* Enemy = GetEnemy(OwnerComp);
	if (Enemy == nullptr) return EBTNodeResult::Failed;
	
	//Enemyのところを示すUIを隠す
	GetEnemy(OwnerComp)->SetEnemyDirectionIndicatorActive(false);

	// MoveTo Startの位置
	OwnerComp.GetAIOwner()->MoveToLocation(Enemy->StartLocation,30);
	return EBTNodeResult::InProgress;
	
}

void UMoveToStartPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// AIControllerの状態がIdleなら
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {
	
		//StateをIdle状態に変更
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Idle);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
