//制作日：2023/07/08　制作者：トウ　更新内容：攻撃アニメーションの間に敵に攻撃処理を行うためのアニメーションノーティファイを作成


#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Attacking_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttacking_AN : public UAnimNotifyState
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
