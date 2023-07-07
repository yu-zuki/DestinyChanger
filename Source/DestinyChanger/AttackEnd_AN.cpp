// Fill out your copyright notice in the Description page of Project Settings.


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
