// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAssistComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttackAssistComponent::UAttackAssistComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAttackAssistComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UAttackAssistComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/// \brief 攻撃の角度を最も近い敵に修正する。
void UAttackAssistComponent::CorrectAttackAngle()
{
	AActor* NearestEnemy = SelectNearestEnemy();	// 最も近い敵を取得する

	if (NearestEnemy != nullptr) {
	
		// プレイヤーと敵の方向を取得する
		FVector direction = NearestEnemy->GetActorLocation() - GetOwner()->GetActorLocation();
		direction.Normalize();

		// プレイヤーの向きを取得する
		FRotator CurrentRotation = GetOwner()->GetActorRotation();

		// プレイヤーの向きを変更する
		FRotator NewRotation(CurrentRotation.Pitch, direction.Rotation().Yaw, CurrentRotation.Roll);
		GetOwner()->SetActorRotation(NewRotation);
	}
}

/// \brief 最も近い敵を選択する
AActor* UAttackAssistComponent::SelectNearestEnemy()
{
	if (EnemyBaseClass == nullptr)	{

		// エラー処理
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: EnemyBaseClass is nullptr"));
		return nullptr;
	}

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

