// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEnd_AN.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChanger/DestinyChangerGameMode.h"


void UAttackEnd_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GameMode ‚ðŽæ“¾
	ADestinyChangerGameMode* GameMode = Cast<ADestinyChangerGameMode>(UGameplayStatics::GetGameMode(MeshComp->GetWorld()));
	if (GameMode)	{
		GameMode->AttackEndEventCall();	//
	}
}
