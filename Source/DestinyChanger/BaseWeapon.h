//制作日：2023/07/08　制作者：トウ　処理内容：武器の処理
//制作日：2023/07/09　制作者：トウ　更新内容：HitStop、HitEffect、Damgeを追加


#pragma once

#include "CoreMinimal.h"
#include "BaseEquippable.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API ABaseWeapon : public ABaseEquippable
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	virtual void BeginPlay() override;

	//オーバーラップイベント
	//void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) override;

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float fAttackPower = 10.0f;	//ダメージ

	float fDefaultAttackPower = 0.f;	//デフォルトのダメージ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FName HandSocketName;	//装備時のアタッチ先

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UCapsuleComponent* WeaponCollision;	//武器の当たり判定

	//Niagara Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UNiagaraSystem* HitEffect;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bIsAttachToHand = true;	//手に装備するか？

	UFUNCTION(BlueprintPure, Category = "Weapon")
		bool GetIsAttachToHand() const { return bIsAttachToHand; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetIsAttachToHand(bool bNewAttachToHand) { bIsAttachToHand = bNewAttachToHand; }

	void AttachToHand();
	void DetachFromHand();

	UFUNCTION(BlueprintPure, Category = "Weapon")
		FName GetHandSocketName() const { return HandSocketName; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetHandSocketName(FName NewSocketName) { HandSocketName = NewSocketName; }

	virtual void OnEquipped() override;
	virtual void OnUnequipped() override;

	void CheckOverlap();	//オーバーラップをチェックする
	void EnemyOnOverlap(struct FHitResult& _HitResult);	//敵とOverrap時の処理
	void EnemyOnOverlap(class AActor* EnemyActor,FVector HitLocation);	//敵とOverrap時の処理

	//攻撃力の倍率を一時的に変更する
	void SetAttackPowerRatio(float _DamageRatio = 2.f);

	//攻撃力の倍率を元に戻す
	void ResetAttackPowerRatio(){ fAttackPower = fDefaultAttackPower; }

	//攻撃力を取得する
	float GetAttackPower() const { return fAttackPower; }
};