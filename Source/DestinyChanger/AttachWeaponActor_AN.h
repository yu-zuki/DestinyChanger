//������F2023/07/08�@����ҁF�g�E�@�������e�F������v���C���[�̎�ɖ߂��@AND�@���ɖ߂��@�̃A�j���[�V�����ݒ�

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
