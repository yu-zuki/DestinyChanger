//������F2023/07/08�@����ҁF�g�E�@�������e�F�G�̃_���[�W�󂯂̃t���O�����Z�b�g

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
