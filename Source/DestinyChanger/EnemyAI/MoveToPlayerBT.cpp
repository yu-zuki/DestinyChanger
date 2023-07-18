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
	// Enemy‚ðŽæ“¾
	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	// NavigationSystem‚ðŽæ“¾
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys == nullptr) return EBTNodeResult::Failed;

	// Player‚ðŽæ“¾
	OwnerComp.GetAIOwner()->MoveToActor( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 50 );
	return EBTNodeResult::InProgress;
}

void UMoveToPlayerBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// AIController‚Ìó‘Ô‚ªIdle‚È‚ç
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Attack);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
