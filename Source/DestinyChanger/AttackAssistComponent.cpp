// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAssistComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"

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
	//機能使用するかどうかのチェック
	if (!bUseCorrectAttackAngle) return;

	//処理内容
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

void UAttackAssistComponent::HitStop(float _HitStopSpeed)
{
	//機能使用するかどうかのチェック
	if (!bUseHitStop) return;

	//処理内容
	ACharacter* Character = Cast<ACharacter>(GetOwner());		//CharacterGet
	if (Character == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: Character is nullptr"));
		return;
	}

	//HitStopを開始
	Character->GetMesh()->GlobalAnimRateScale = _HitStopSpeed > 0.f ? _HitStopSpeed : HitStopSpeed;

	//HitStopを停止
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(TimerHandle_HitStop, this, &UAttackAssistComponent::HitStopProcess, HitStopTime, false);
}

void UAttackAssistComponent::HitEffect(UNiagaraSystem* _NiagaraSystem, FVector _HitLocation, FVector _HitDirection)
{
	//機能使用するかどうかのチェック
	if (!bUseHitEffect) return;

	//処理内容
	if (_NiagaraSystem == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: NiagaraSystem is nullptr"));
		return;
	}

	FVector AntiHitDirection = _HitDirection * -1;
	FRotator HitRotation = FRotator(AntiHitDirection.Rotation().Pitch, 0.f, 0.f);

	FVector Scale = FVector(0.7f, 0.7f, 0.7f);
	//Spawn
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),_NiagaraSystem,_HitLocation,HitRotation,Scale);
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

void UAttackAssistComponent::HitStopProcess()
{
	//CharacterGet
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: Character is nullptr"));
		return;
	}

	//HitStopを停止
	Character->GetMesh()->GlobalAnimRateScale = 1.f;
}

