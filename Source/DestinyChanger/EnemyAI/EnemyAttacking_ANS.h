//�X�V���F2023/07/21�@�X�V�ҁF�g�E�@�X�V���e�F�G�̍U�����̒ʒm

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
