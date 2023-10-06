//制作日：2023/07/08　制作者：トウ　処理内容：武器をプレイヤーの手に戻す　AND　腰に戻す　のアニメーション設定



#include "AttachWeaponActor_AN.h"
#include "DestinyChangerCharacter.h"
#include "BaseWeapon.h"

UAttachWeaponActor_AN::UAttachWeaponActor_AN()
{
}

void UAttachWeaponActor_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ADestinyChangerCharacter* Character = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner()); //get character
	if (Character) {
		ABaseWeapon* MainWeapon = Character->GetMainWeapon();			//get main weapon
		if (MainWeapon) {
			if (MainWeapon->GetIsAttachToHand()) {
				MainWeapon->AttachToHand();
			}
			else {
				MainWeapon->DetachFromHand();
			}
		}
	}
	else	{
		UE_LOG(LogTemp, Warning, TEXT("Character is not found"));
	}
}
