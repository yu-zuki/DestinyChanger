//制作日：2023/07/18　制作者：トウ　処理内容：プレイヤーに追うのTask

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

	//最大の移動の範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float fMaxMoveRange = 4000.0f;
};
