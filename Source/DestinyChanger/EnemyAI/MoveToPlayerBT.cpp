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
	// Enemy���擾
	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	// NavigationSystem���擾
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys == nullptr) return EBTNodeResult::Failed;

	// Player�̏��Ɉړ��J�n
	OwnerComp.GetAIOwner()->MoveToActor( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 50 );
	return EBTNodeResult::InProgress;
}

void UMoveToPlayerBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Enemy���擾
	AEnemyBase* Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy == nullptr) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//���݂̋�����Start���̋����Ɓ@fMaxMoveRange �ȏ㗣��Ă�����
	float Distance = FVector::Distance(Enemy->GetActorLocation(), Enemy->StartLocation);
	if (Distance > fMaxMoveRange) {
		//State���v���C���[��T����ԂɕύX
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Return);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	// AIController�̏�Ԃ�Idle�Ȃ�i�v���C���[�̏��ɂ��ǂ蒅������j
	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Idle) {

		//State���v���C���[���U�������ԂɕύX
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Attack);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
