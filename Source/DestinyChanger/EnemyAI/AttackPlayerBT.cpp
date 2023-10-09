// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPlayerBT.h"
#include "../EnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy_BD.h"

UAttackPlayerBT::UAttackPlayerBT()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackPlayerBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsAttackEnd = false;

	//�G�̎擾
	AEnemyBase* Enemy = GetEnemy(OwnerComp);

	if (Enemy == nullptr) 	return EBTNodeResult::Failed;
	if (Enemy->AttackAnimMontage == nullptr) 	return EBTNodeResult::Failed;

	//Player�̎擾
	APawn* Player =  GetWorld()->GetFirstPlayerController()->GetPawn() ;
	if (Player == nullptr) 	return EBTNodeResult::Failed;

	//�G�̌������v���C���[�̕����Ɍ�����
	FRotator NewRot = (Player->GetActorLocation() - Enemy->GetActorLocation()).Rotation();
	NewRot.Pitch = 0.0f;
	NewRot.Roll = 0.0f;
	Enemy->SetActorRotation(NewRot);

	//Enemy�̂Ƃ��������UI��\��
	Enemy->SetEnemyDirectionIndicatorActive(true);

	//�U���̃A�j���[�V�������Đ�
	float tmp_TimeCount = Enemy->PlayAnimMontage(Enemy->AttackAnimMontage);

	//�U���̃A�j���[�V�����̍Đ����Ԃ��擾
	tmp_TimeCount *= Enemy->AttackAnimMontage->RateScale;

	//�U���̃A�j���[�V�����̍Đ����ԕ��A�U�����s��Ȃ��悤�ɂ���
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(TimerHandle_AttackEnd, this, &UAttackPlayerBT::AttackEnd, tmp_TimeCount, false);

	return EBTNodeResult::InProgress;
}

void UAttackPlayerBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bIsAttackEnd)	{
		//State���v���C���[���v���C���[�ɒǐՂ̏�ԂɕύX
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Chase);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UAttackPlayerBT::AttackEnd()
{
	bIsAttackEnd = true;
}