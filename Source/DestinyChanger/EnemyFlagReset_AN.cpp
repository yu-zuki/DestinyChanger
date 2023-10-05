//制作日：2023/07/08　制作者：トウ　処理内容：敵のダメージ受けのフラグをリセット


#include "EnemyFlagReset_AN.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChanger/DestinyChangerGameMode.h"

void UEnemyFlagReset_AN::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	//GameMode を取得
	ADestinyChangerGameMode* GameMode = Cast<ADestinyChangerGameMode>(UGameplayStatics::GetGameMode(MeshComp->GetWorld()));
	if (GameMode) {
		GameMode->AttackEndEventCall();	//
	}
}
