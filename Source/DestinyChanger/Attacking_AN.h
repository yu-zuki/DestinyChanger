//������F2023/07/08�@����ҁF�g�E�@�������e�F�U���A�N�V�����̓���̃t���[���̊ԂɓG�ɍU������

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
