// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAssistComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttackAssistComponent::UAttackAssistComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackAssistComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackAssistComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackAssistComponent::CorrectAttackAngle()
{
	AActor* NearestEnemy = SelectNearestEnemy();	// 最も近い敵を取得する

	if (NearestEnemy != nullptr) {
	
		// プレイヤーと敵の方向を取得する
		FVector direction = NearestEnemy->GetActorLocation() - GetOwner()->GetActorLocation();
		direction.Normalize();

		// プレイヤーの向きを変更する
		GetOwner()->SetActorRotation(direction.Rotation());		
	}
}

AActor* UAttackAssistComponent::SelectNearestEnemy()
{
	// 全ての敵を取得する
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyBaseClass, FoundEnemies);

	float MinDistance = MAX_FLT;
	AActor* NearestEnemy = nullptr;

	for ( auto enemy : FoundEnemies)
	{
		// プレイヤーと敵の距離を取得する
		float distance = FVector::Distance(GetOwner()->GetActorLocation(), enemy->GetActorLocation());

		if (IsInSearchRange(distance)){
			if (distance < MinDistance) {
				MinDistance = distance;
				NearestEnemy = enemy;
			}
		}
	}
	
	if (NearestEnemy != nullptr) {
		return NearestEnemy;
	}

	return nullptr;
}

