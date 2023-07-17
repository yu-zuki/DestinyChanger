// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy_AIC.h"

void ABaseEnemy_AIC::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy_AIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//ビヘイビアツリーの開始
	if (BehaviorTree) {
		RunBehaviorTree(BehaviorTree);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("BehaviorTree is not found"));
	}
}
