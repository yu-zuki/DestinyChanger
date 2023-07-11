//������F2023/07/12�@����ҁF�g�E�@�������e�F�U�����̃G�t�F�N�g�F���q�G�t�F�N�g

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState_TimedParticleEffect.h"
#include "AttackEffectParticle_ANS.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttackEffectParticle_ANS : public UAnimNotifyState_TimedParticleEffect
{
	GENERATED_BODY()
	
	//���q�G�t�F�N�g�̃X�|�[���ʒu
	UPROPERTY(EditAnywhere, Category = ParticleSystem, meta = (ToolTip = "The socket or bone to attach the system to"))
	FName SocketName2;

	UPROPERTY(EditAnywhere, Category = ParticleSystem, meta = (ToolTip = "The socket or bone to attach the system to"))
	FName SocketName3;
public:
	//���q�G�t�F�N�g�̃X�|�[���Ə��ŏ���
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
