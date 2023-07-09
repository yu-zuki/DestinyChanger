// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackAssistComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UAttackAssistComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttackAssistComponent();

	/// コンポーネント開始時の動作。
	virtual void BeginPlay() override;

	/// フレーム毎の動作。
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// 攻撃の角度を修正する。
	void CorrectAttackAngle();

	/// 最も近い敵を選択する。
	AActor* SelectNearestEnemy();

protected:

	/// 敵を表すベースとなるアクタークラス。
	UPROPERTY(EditAnywhere, Category = "Attack Assist")
		TSubclassOf<AActor> EnemyBaseClass;

	// 攻撃範囲内にいる敵を判定するための距離 (単位cm)。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float MaxSearchDistance = 300.f;

private:

	//MinDistanceの範囲内かどうかを判定する
	inline bool IsInSearchRange(float distance)	{	return distance <= MaxSearchDistance;	}
};
