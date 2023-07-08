// Fill out your copyright notice in the Description page of Project Settings.


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
