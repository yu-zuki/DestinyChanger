// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeformRollComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFreeformRollComponent::UFreeformRollComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UFreeformRollComponent::BeginPlay()
{
	Super::BeginPlay();
}

/// \brief Roll���������s����
void UFreeformRollComponent::RollProcess()
{
	if (bIsRolling) return;

	//Character Get
	ACharacter* Character = CastChecked<ACharacter>(GetOwner());

	//Roll�����^�[�W�����Đ�
	if (RollMontage)	{
		bIsRolling = true;
		float _animeTime = Character->PlayAnimMontage(RollMontage);

		//SetTimer
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();

		_animeTime += RollCD;
		FTimerHandle TimerHandle;
		TimerManager.SetTimer(TimerHandle,this, &UFreeformRollComponent::ResetRollValue, _animeTime, false);
	}
}

void UFreeformRollComponent::ResetRollValue()
{
	bIsRolling = false;
}
