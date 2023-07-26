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
	// Enemy���擾
	AEnemyBase* Enemy = GetEnemy(OwnerComp);
	if (Enemy == nullptr) return EBTNodeResult::Failed;
	
	//Enemy�̂Ƃ��������UI���B��
	GetEnemy(OwnerComp)->SetEnemyDirectionIndicatorActive(false);

	// MoveTo Start�̈ʒu
	OwnerComp.GetAIOwner()->MoveToLocation(Enemy->StartLocation,30);
	return EBTNodeResult::InProgress;
	
}

void UMoveToStartPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// AIController�̏�Ԃ�Idle�Ȃ�
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {
	
		//State��Idle��ԂɕύX
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Idle);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
