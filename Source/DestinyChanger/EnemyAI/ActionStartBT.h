//������F2023/07/20�@����ҁF�g�E�@�������e�F�G�̑ҋ@��Ԃ�Task
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyTaskBase_BT.h"
#include "ActionStartBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UActionStartBT : public UEnemyTaskBase_BT
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
