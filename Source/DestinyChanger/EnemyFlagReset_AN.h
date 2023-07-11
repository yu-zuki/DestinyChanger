//制作日：2023/07/08　制作者：トウ　処理内容：敵のダメージ受けのフラグをリセット

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyFlagReset_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UEnemyFlagReset_AN : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
