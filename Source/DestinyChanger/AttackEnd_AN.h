//制作日：2023/07/09　制作者：トウ　更新内容：攻撃終了時、プレイヤーが攻撃可能になる


#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackEnd_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttackEnd_AN : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
public:
};
