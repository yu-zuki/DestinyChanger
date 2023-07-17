// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RandomMoveBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API URandomMoveBT : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URandomMoveBT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	//�����_���ړ��͈̔�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float RandomMoveRange = 500.0f;

	//�v���C���[��������͈�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float FindPlayerRange = 1000.0f;
};