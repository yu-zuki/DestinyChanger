//制作日：2023/07/09　制作者：トウ　処理内容：攻撃終了時、プレイヤーの攻撃操作フラグをリセット

#include "AttackEnd_AN.h"
#include "DestinyChangerCharacter.h"

void UAttackEnd_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//プレイヤーを取得
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner());
	if (Player)	{
		Player->bIsAttacking = false;
	}
}
