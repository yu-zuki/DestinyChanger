//������F2023/07/08�@����ҁF�g�E�@�X�V���e�F�U���A�j���[�V�����̊ԂɓG�ɍU���������s�����߂̃A�j���[�V�����m�[�e�B�t�@�C���쐬


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
