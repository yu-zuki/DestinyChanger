//更新日：2023/07/21　更新者：トウ　更新内容：敵の攻撃中の通知

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EnemyAttacking_ANS.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UEnemyAttacking_ANS : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference
	) override;
	
};
