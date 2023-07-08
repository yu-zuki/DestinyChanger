// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFlagReset_AN.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChanger/DestinyChangerGameMode.h"

void UEnemyFlagReset_AN::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	//GameMode ‚ðŽæ“¾
	ADestinyChangerGameMode* GameMode = Cast<ADestinyChangerGameMode>(UGameplayStatics::GetGameMode(MeshComp->GetWorld()));
	if (GameMode) {
		GameMode->AttackEndEventCall();	//
	}
}
