// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyTaskBase_BT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UEnemyTaskBase_BT : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	class AEnemyBase* EnemyPtr = nullptr;

	class AEnemyBase* GetEnemy(UBehaviorTreeComponent& OwnerComp);
};
