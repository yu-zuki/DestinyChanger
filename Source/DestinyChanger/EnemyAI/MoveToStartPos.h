// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyTaskBase_BT.h"
#include "MoveToStartPos.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UMoveToStartPos : public UEnemyTaskBase_BT
{
	GENERATED_BODY()

public:
	UMoveToStartPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
