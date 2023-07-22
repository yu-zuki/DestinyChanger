// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase_UMG.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UCharacterBase_UMG::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (HealthBar)
	{
		HealthBar->SetPercent( GetHPPercent() );
	}
}

void UCharacterBase_UMG::SetPlayerInfo(float HP, float MaxHP)
{
	fHP = HP;
	fMaxHP = MaxHP;
}
