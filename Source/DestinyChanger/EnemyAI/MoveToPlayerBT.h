//������F2023/07/18�@����ҁF�g�E�@�������e�F�v���C���[�ɒǂ���Task

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToPlayerBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UMoveToPlayerBT : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMoveToPlayerBT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//�ő�̈ړ��͈̔�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float fMaxMoveRange = 4000.0f;
};
