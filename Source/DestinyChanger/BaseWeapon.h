//制作日：2023/07/08　制作者：トウ　更新内容：武器の基礎クラス


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
	virtual void BeginPlay() override;

	//オーバーラップイベント
	//void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		FName HandSocketName;	//装備時のアタッチ先


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		bool bIsAttachToHand = true;	//手に装備するか？

	UFUNCTION(BlueprintPure, Category = "Attachment")
		bool GetIsAttachToHand() const { return bIsAttachToHand; }

	UFUNCTION(BlueprintCallable, Category = "Attachment")
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
	void EnemyOnOverlap(class AActor* EnemyActor);	//敵とOverrap時の処理
};
