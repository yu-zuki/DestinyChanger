// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachWeaponActor_AN.h"
#include "DestinyChangerCharacter.h"
#include "BaseWeapon.h"


UAttachWeaponActor_AN::UAttachWeaponActor_AN()
	:bIsAttachToHand(false)
{
}

void UAttachWeaponActor_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ADestinyChangerCharacter* Character = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner()); //get character
	if (Character) {
		ABaseWeapon* MainWeapon = Character->GetMainWeapon();			//get main weapon
		if (MainWeapon) {

			FName tmp_AttachScoket = MainWeapon->GetAttachSocketName();	//get attach scoket name
			FName tmp_HandScoket = MainWeapon->GetHandSocketName();		//get hand scoket name

			if (bIsAttachToHand) //is hand scoket			
			{
				MainWeapon->AttachActor(tmp_HandScoket);				//attach to hand
			}
			else {
				MainWeapon->AttachActor(tmp_AttachScoket);				//attach to attach scoket
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is not found"));
	}
}
