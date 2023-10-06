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

/**
 * @brief キャラクターの情報をUIに設定します。
 * 
 * @details キャラクターの現在HPと最大HPをUIに設定します。
 * 
 * @param HP キャラクターの現在HP
 * 
 * @param MaxHP キャラクターの最大HP
 */
void UCharacterBase_UMG::SetPlayerInfo(float HP, float MaxHP)
{
	fHP = HP;
	fMaxHP = MaxHP;
}
