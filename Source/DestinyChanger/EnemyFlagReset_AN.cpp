//������F2023/07/08�@����ҁF�g�E�@�������e�F�G�̃_���[�W�󂯂̃t���O�����Z�b�g


#include "EnemyFlagReset_AN.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChanger/DestinyChangerGameMode.h"

void UEnemyFlagReset_AN::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	//GameMode ���擾
	ADestinyChangerGameMode* GameMode = Cast<ADestinyChangerGameMode>(UGameplayStatics::GetGameMode(MeshComp->GetWorld()));
	if (GameMode) {
		GameMode->AttackEndEventCall();	//
	}
}
