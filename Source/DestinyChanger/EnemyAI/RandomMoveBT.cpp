﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMoveBT.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "..//EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy_BD.h"


URandomMoveBT::URandomMoveBT()
{
	bNotifyTick = true;
}

EBTNodeResult::Type URandomMoveBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Enemyを取得
	AEnemyBase* Enemy = GetEnemy(OwnerComp);
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	//Enemyのところを示すUIを隠す
	GetEnemy(OwnerComp)->SetEnemyDirectionIndicatorActive(false);

	// NavigationSystemを取得
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys == nullptr) return EBTNodeResult::Failed;

	// ランダムの位置を取得
	FVector RandomLocation;
	if (NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), Enemy->StartLocation, RandomLocation, RandomMoveRange)) {
		// MoveTo ランダムの位置
		OwnerComp.GetAIOwner()->MoveToLocation(RandomLocation);
		return EBTNodeResult::InProgress;
	}
	else {
		return EBTNodeResult::Failed;
	}
}

void URandomMoveBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//移動中、プレイヤーとの距離が一定以下なら
	if (GetEnemy(OwnerComp)->GetDistanceTo( UGameplayStatics::GetPlayerCharacter( GetWorld(),0 ) ) < FindPlayerRange) {
		
		//Stateをプレイヤーを追いかける状態に変更
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Chase);

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);	//タスクを終了
		return;
	}

	// AIControllerの状態がIdleなら
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
