//制作日：2023/07/08　制作者：トウ　処理内容：武器をプレイヤーの手に戻す　AND　腰に戻す　のアニメーション設定

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttachWeaponActor_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttachWeaponActor_AN : public UAnimNotify
{
	GENERATED_BODY()
	
	UAttachWeaponActor_AN();
protected:

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
