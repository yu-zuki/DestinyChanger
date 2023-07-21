//������F2023/07/08�@����ҁF�g�E�@�������e�F����̏���
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�FHitStop�AHitEffect�ADamge��ǉ�


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

	//�I�[�o�[���b�v�C�x���g
	//void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) override;

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float fDamage = 10.0f;	//�_���[�W

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FName HandSocketName;	//�������̃A�^�b�`��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UCapsuleComponent* WeaponCollision;	//����̓����蔻��

	//Niagara Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UNiagaraSystem* HitEffect;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bIsAttachToHand = true;	//��ɑ������邩�H

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

	void CheckOverlap();	//�I�[�o�[���b�v���`�F�b�N����
	void EnemyOnOverlap(struct FHitResult& _HitResult);	//�G��Overrap���̏���
	void EnemyOnOverlap(class AActor* EnemyActor,FVector HitLocation);	//�G��Overrap���̏���

	//�_���[�W�̔{�����ꎞ�I�ɕύX����
	void SetDamageRatio(float _DamageRatio = 2.f);
};