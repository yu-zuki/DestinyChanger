//������F2023/07/09�@����ҁF�g�E�@�������e�F�U���I�����A�v���C���[�̍U������t���O�����Z�b�g
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
