//������F2023/07/09�@����ҁF�g�E�@�������e�F�U���I�����A�v���C���[�̍U������t���O�����Z�b�g

#include "AttackEnd_AN.h"
#include "DestinyChangerCharacter.h"

void UAttackEnd_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//�v���C���[���擾
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner());
	if (Player)	{
		Player->bIsAttacking = false;
	}
}
