// Fill out your copyright notice in the Description page of Project Settings.


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
