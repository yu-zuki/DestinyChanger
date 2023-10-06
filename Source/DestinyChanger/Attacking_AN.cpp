//制作日：2023/07/08　制作者：トウ　処理内容：攻撃アクションの特定のフレームの間に敵に攻撃処理


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
