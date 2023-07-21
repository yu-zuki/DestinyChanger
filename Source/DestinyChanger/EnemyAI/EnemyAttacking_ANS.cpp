// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttacking_ANS.h"
#include "../EnemyBase.h"


void UEnemyAttacking_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//Enemy Get
	AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
	if (Enemy) {
		Enemy->HitDecect();
	}
}
