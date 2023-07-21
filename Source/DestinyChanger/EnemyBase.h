//������F2023/07/08�@����ҁF�g�E�@�������e�F�G�̏���
//������F2023/07/08�@����ҁF�g�E�@�X�V���e�F�G�̊�{����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DestinyChangerGameMode.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

#include "EnemyBase.generated.h"

UCLASS()
class DESTINYCHANGER_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	//tick
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

//////////
///Anime
public:

	//�_���[�W�󂯂����̃A�j���[�V����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackedAnimMontage;

	//���S���̃A�j���[�V����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* DeathAnimMontage;

	//�U�����̃A�j���[�V����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackAnimMontage;

//////////
///HP
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float MaxHP = 100.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Damage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Heal(float Heal);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Death();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		bool bIsAttacked = false;				//�U�����󂯂����ǂ���

	void ResetIsAttacked(); 

	//GetHP
	UFUNCTION(BlueprintCallable, Category = "HP")
		float GetHP() { return HP; }

//////////////////////////////////////////////////////////////////////////
///UI
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UBase_WidgetComponent* EnemyWidget;

		class UUserWidget* EnemyDirectionIndicator;		//Enemy�̕���������UI

//////////////////////////////////////////////////////////////////////////
///AI
public:

	FVector StartLocation;		//�����ʒu

//////////////////////////////////////////////////////////////////////////
///�U��
	float AttackDamage = 10.0f;		//�U����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UCapsuleComponent* AttackCollisionComponent;	//�U���̓����蔻��

	virtual void HitDecect();

	virtual void CheckOverlap(class UCapsuleComponent* _AttackCollision);
//////////
///�擾
protected:
	inline class ADestinyChangerGameMode* GetGameMode();
public:
	// static ADestinyChangerGameMode* GameMode;
	ADestinyChangerGameMode* GameMode;
};
