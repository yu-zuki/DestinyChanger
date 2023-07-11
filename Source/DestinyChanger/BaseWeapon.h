//������F2023/07/08�@����ҁF�g�E�@�X�V���e�F����̊�b�N���X


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

	//�I�[�o�[���b�v�C�x���g
	//void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		FName HandSocketName;	//�������̃A�^�b�`��


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		bool bIsAttachToHand = true;	//��ɑ������邩�H

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

	void CheckOverlap();	//�I�[�o�[���b�v���`�F�b�N����
	void EnemyOnOverlap(class AActor* EnemyActor);	//�G��Overrap���̏���
};
