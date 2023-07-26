//制作日：2023/07/20　制作者：トウ　処理内容：プレイヤーに攻撃するTask

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyTaskBase_BT.h"
#include "AttackPlayerBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttackPlayerBT : public UEnemyTaskBase_BT
{
	GENERATED_BODY()
public:

	UAttackPlayerBT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	bool bIsAttackEnd = false;

	FTimerHandle TimerHandle_AttackEnd;

	void AttackEnd();

};
