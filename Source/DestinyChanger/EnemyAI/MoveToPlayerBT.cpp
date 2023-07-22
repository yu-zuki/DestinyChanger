// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPlayerBT.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "..//EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseEnemy_BD.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/BlackboardComponent.h"

UMoveToPlayerBT::UMoveToPlayerBT()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveToPlayerBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Enemyを取得
	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	// NavigationSystemを取得
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys == nullptr) return EBTNodeResult::Failed;

	// Playerの所に移動開始
	OwnerComp.GetAIOwner()->MoveToActor( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 50 );
	return EBTNodeResult::InProgress;
}

void UMoveToPlayerBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Enemyを取得
	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy == nullptr) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//現在の距離はStart時の距離と　fMaxMoveRange 以上離れていたら
	float Distance = FVector::Distance(Enemy->GetActorLocation(), Enemy->StartLocation);
	if (Distance > fMaxMoveRange) {
		//Stateをプレイヤーを探す状態に変更
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Return);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	// AIControllerの状態がIdleなら（プレイヤーの所にたどり着いたら）
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {

		//Stateをプレイヤーを攻撃する状態に変更
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Attack);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
