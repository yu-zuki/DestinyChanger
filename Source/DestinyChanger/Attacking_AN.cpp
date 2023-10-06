//������F2023/07/08�@����ҁF�g�E�@�������e�F�U���A�N�V�����̓���̃t���[���̊ԂɓG�ɍU������


#include "Attacking_AN.h"
#include "DestinyChangerCharacter.h"

void UAttacking_AN::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//PlayerGet
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner());
	if (Player)	{
		Player->HitDecect();
	}
}
