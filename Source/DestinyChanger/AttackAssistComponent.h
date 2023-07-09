//制作日：2023/07/09　制作者：トウ　更新内容：プレイヤー角度の修正を行う処理を追加
//制作日：2023/07/09　制作者：トウ　更新内容：プレイヤーが敵を攻撃した際にHitStop処理を追加
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

	//HitStopを行う
	void HitStop(float _HitStopSpeed = -1.f);

private:
	/// 最も近い敵を選択する。
	AActor* SelectNearestEnemy();

	//MinDistanceの範囲内かどうかを判定する
	inline bool IsInSearchRange(float distance)	{	return distance <= MaxSearchDistance;	}

	//HitStop処理
	void HitStopProcess();


protected:
	/// 敵を表すベースとなるアクタークラス。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Assist")
		TSubclassOf<AActor> EnemyBaseClass;

	// 攻撃範囲内にいる敵を判定するための距離 (単位cm)。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float MaxSearchDistance = 300.f;

	//HitStopの速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float HitStopSpeed = 0.01f;

	//HitStopの時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float HitStopTime = 0.2f;

private:
	FTimerHandle TimerHandle_HitStop;
};
