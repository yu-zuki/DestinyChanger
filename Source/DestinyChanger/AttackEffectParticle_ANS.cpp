//制作日：2023/07/12　制作者：トウ　処理内容：攻撃時のエフェクト：粒子エフェクト


#include "AttackEffectParticle_ANS.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

//　UEがデフォルトのParticleの処理は1個しか生成できないので、
//　3個のParticleを生成するために、以下のコードを追加（Superを使用せずにUEの処理を破棄 ）

void UAttackEffectParticle_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	// ensure deprecated path is called because a call to Super is not made
	//PRAGMA_DISABLE_DEPRECATION_WARNINGS
		//NotifyBegin(MeshComp, Animation, TotalDuration);
	//PRAGMA_ENABLE_DEPRECATION_WARNINGS
		// Only spawn if we've got valid params
		if (ValidateParameters(MeshComp))
		{
			UParticleSystemComponent* NewComponent = UGameplayStatics::SpawnEmitterAttached(PSTemplate, MeshComp, SocketName, LocationOffset, RotationOffset, EAttachLocation::KeepRelativeOffset, !bDestroyAtEnd);
			UParticleSystemComponent* NewComponent2 = UGameplayStatics::SpawnEmitterAttached(PSTemplate, MeshComp, SocketName2, LocationOffset, RotationOffset, EAttachLocation::KeepRelativeOffset, !bDestroyAtEnd);
			UParticleSystemComponent* NewComponent3 = UGameplayStatics::SpawnEmitterAttached(PSTemplate, MeshComp, SocketName3, LocationOffset, RotationOffset, EAttachLocation::KeepRelativeOffset, !bDestroyAtEnd);
		}
	Received_NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UAttackEffectParticle_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//PRAGMA_DISABLE_DEPRECATION_WARNINGS
		//NotifyEnd(MeshComp, Animation);
	//PRAGMA_ENABLE_DEPRECATION_WARNINGS
		TArray<USceneComponent*> Children;
	MeshComp->GetChildrenComponents(false, Children);

	for (USceneComponent* Component : Children)
	{
		if (UParticleSystemComponent* ParticleComponent = Cast<UParticleSystemComponent>(Component))
		{
			if (bDestroyAtEnd)
			{
				ParticleComponent->DestroyComponent();
			}
			else
			{
				ParticleComponent->DeactivateSystem();
			}
		}
	}

	Received_NotifyEnd(MeshComp, Animation, EventReference);
}
