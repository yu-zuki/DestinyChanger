//制作日：2023/07/12　制作者：トウ　処理内容：攻撃時のエフェクト：粒子エフェクト

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
	
	//粒子エフェクトのスポーン位置
	UPROPERTY(EditAnywhere, Category = ParticleSystem, meta = (ToolTip = "The socket or bone to attach the system to"))
	FName SocketName2;

	UPROPERTY(EditAnywhere, Category = ParticleSystem, meta = (ToolTip = "The socket or bone to attach the system to"))
	FName SocketName3;
public:
	//粒子エフェクトのスポーンと消滅処理
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
