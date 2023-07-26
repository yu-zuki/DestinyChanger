//制作日：2023/07/18　制作者：トウ　処理内容：ある程度の範囲内で移動するTask

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyTaskBase_BT.h"
#include "RandomMoveBT.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API URandomMoveBT : public UEnemyTaskBase_BT
{
	GENERATED_BODY()

public:
	URandomMoveBT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	//ランダム移動の範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float RandomMoveRange = 500.0f;

	//プレイヤーを見つける範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomMove")
		float FindPlayerRange = 1000.0f;
};
