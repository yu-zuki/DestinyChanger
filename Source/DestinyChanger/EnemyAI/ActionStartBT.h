//制作日：2023/07/20　制作者：トウ　処理内容：敵の待機状態のTask
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ActionStartBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UActionStartBT : public UBTTaskNode
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
