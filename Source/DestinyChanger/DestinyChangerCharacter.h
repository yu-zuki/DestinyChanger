//������F2023/07/08�@����ҁF�g�E�@�������e�F�v���C���[�̏���
//������F2023/07/08�@����ҁF�g�E�@�X�V���e�F�U�����[�V�����̒ǉ�
//�X�V���F2023/07/09�@�X�V�ҁF�g�E�@�X�V���e�F�U���R���{�̒ǉ�
//�X�V���F2023/07/09�@�X�V�ҁF�g�E�@�X�V���e�F����A�N�V�����̒ǉ�
//�X�V���F2023/07/13�@�X�V�ҁF�g�E�@�X�V���e�F�_���[�W�󂯏����̒ǉ�
//�X�V���F2023/07/14�@�X�V�ҁF�g�E�@�X�V���e�F�G�l�~�[�̕����������R���|�[�l���g�̒ǉ�
//�X�V���F2023/07/21�@�X�V�ҁF�g�E�@�X�V���e�F�h�䏈���̒ǉ�
//�X�V���F2023/07/22�@�X�V�ҁF�g�E�@�X�V���e�FUI�̒ǉ�
//�X�V���F2023/07/23�@�X�V�ҁF�g�E�@�X�V���e�FDestinySystem�̒ǉ�
//�X�V���F2023/07/30�@�X�V�ҁF�g�E�@�X�V���e�FGuard�̒ǉ�
//�X�V���F2023/08/07�@�X�V�ҁF�g�E�@�X�V���e�FInteractSystem�̒ǉ�
//�X�V���F2023/08/25�@�X�V�ҁF�g�E�@�X�V���e�FQuestSystem�̒ǉ�


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "DestinyChangerCharacter.generated.h"

//�U���R���{
enum class EAttackComb : uint8
{
	LightAttackNone,
	LightAttackOne,
	LightAttackTwo,
	LightAttackThree,
	LightAttackFour,
};

//Level Data
USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 iLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fLevelExp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fLevelUpExp = 100.0f;
};

UCLASS(config=Game)
class ADestinyChangerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	/** Attack Assist Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Assist", meta = (AllowPrivateAccess = "true"))
	class UAttackAssistComponent* AttackAssistComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Assist", meta = (AllowPrivateAccess = "true"))
	class UFreeformRollComponent* FreeformRollComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Assist", meta = (AllowPrivateAccess = "true"))
	class UInteractComponent* InteractComponent;

public:
	ADestinyChangerCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

//new

//////////////
//�U������
public:
	//�U���̃t���O
	bool bIsAttacking;

protected:
	//�y���U���̓���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* LightAttackAction;

	//�d���U���̓���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* HeavyAttackAction;

	//���̓A�N�V�����̏���
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);

	//�U���̃��[�V����1,2,3,4
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* LightAttackMontageOne;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* LightAttackMontageTwo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* LightAttackMontageThree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* LightAttackMontageFour;

	EAttackComb eAttackComb = EAttackComb::LightAttackOne;
	void LightAttackCountUp();

public:
	void HitDecect();	

//////////////
//���폈��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABaseWeapon> MainWeaponClass;	// �v���C���[�̃��C������̃N���X

	class ABaseWeapon* MainWeapon;	// �v���C���[�̃��C������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_WeaponDraw;	    // ������\���郂�[�V����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_WeaponDisarm;	// ��������܂����[�V����

	void ToggleCombat(const FInputActionValue& Value);	// �퓬���[�h�̐؂�ւ�

	//�d���U���̓���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
		class UInputAction* ToggleCombatAction;

	UFUNCTION(BlueprintCallable, Category = "Battle")
		void SetMainWeapon(ABaseWeapon* _Weapon);
	UFUNCTION(BlueprintCallable, Category = "Battle")
		ABaseWeapon* GetMainWeapon() const;

//////////////
//�������
protected:
	//����̓���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* RollAction;

	//����̏���
	void Roll(const FInputActionValue& Value);

public:
	UAttackAssistComponent* GetAttackAssistComponent() const;

//////////////
//EnemyDirectionIndicator�@�G�̕������������
public:
	class UUserWidget* ShowEnemyDirectionIndicator(AActor * _Target);
	UArrowComponent* GetEnemyDirectionIndicator() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UEnemyTargeting> EnemyTargeting_UMG;	// �v���C���[�̃��C������̃N���X

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* EnemyDirectionIndicator;

//////////////
//�_���[�W�󂯏���
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_TakeDamage;	// �_���[�W���󂯂郂�[�V����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_Death;		// ���S���[�V����

	void TakePlayerDamage(float _Damage);	// �_���[�W���󂯂�

	bool bIsInvincible;							// ���G��Ԃ��ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float InvincibleTime;						// ���G��Ԃ̎���

	void InvincibleFlagReset();					// ���G��Ԃ���������

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	void Death();

//////////////////////////////////////////////////////////////////////////
//�h�䏈��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		bool bIsGuarding = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* GuardAction;

	void OnGuard(const FInputActionValue& Value);
	void OffGuard(const FInputActionValue& Value);

	void GuradFlagReset(float _DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float fGuardGauge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float fMaxGuardGauge;

	//CD
	bool bIsGuardGaugeCountDown;

	void GuardGaugeCountUp(float _CompensationFactor);
	void GuardGaugeCountDown(float _CompensationFactor);
	

	// �h�䒆Hit���[�V����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_GuardHit;		

	UFUNCTION(BlueprintCallable)
		void StartParticleSystem();

	UFUNCTION(BlueprintCallable)
		void StopParticleSystem();

//////////////////////////////////////////////////////////////////////////
//DestinySystem
protected:
	//DestinySystem���N������Ƒ����鎞��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DestinySystem", meta = (AllowPrivateAccess = "true"))
		float fDestinySystemAddTime;
	
	//DestinySystem�̍ő厞��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DestinySystem", meta = (AllowPrivateAccess = "true"))
		float fDestinySystemTimeMax;

	//DestinySystem����񔭓�
	void ExecuteDestinySystem();

	//�^�C�}�[�ɐݒ肷�鎞��
	float fDestinySystemTimerLength = 0.f;

	//�^�C�}�[�ɐݒ肷�鎞�Ԃ𑝂₷
	void AddDestinySystemTimerLength();

	//TimerHandle
	FTimerHandle DestinySystemTimerHandle;

	//AttackPowerReset
	void AttackPowerReset();

	//Create AttackPowerReset Timer
	void CreateAttackPowerResetTimer();

	//AttackPower�̔{��
	float fDefaultAttackPowerRatio = 2.1f;

	float fAttackPowerRatio;

	//AttackPower�̔{�������Z�b�g
	void AttackPowerRatioReset();

	//Get AttackPowerRatio
	float GetAttackPowerRatio();

//////////////////////////////////////////////////////////////////////////
//LevelSystem
public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "LevelSystem", meta = (AllowPrivateAccess = "true"))
		FLevelData LevelData;

	float fPower = 1.f;

	//Get Power
	float GetPower() { return fPower; }

	//LevelUp
	void LevelUp();

	//StatusUp
	void StatusUp();

	//AddExp
	void AddExp(float _Exp);


//////////////////////////////////////////////////////////////////////////
//UI
	////UI Class
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UUserWidget* PlayerUI;

	//�����擾
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHPPercent() { return HP / MaxHP; }

	//�����擾
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetGuardGaugePercent();

	//�U���͂��擾
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetAttackPower();

	//DestinySystem�̎c�莞�Ԃ��擾
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetDestinySystemTime();

	//Get Level Exp LevelUpExp Tuprle
	UFUNCTION(BlueprintCallable, Category = "UI")
		FLevelData GetLevelData() { return LevelData; }


//////////////////////////////////////////////////////////////////////////
//QuestSystem
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	class UQuestSystem* QuestSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	class UQuestGiverComponent* QuestGiverrComponent;

	//QuestSystem���R���v���[�g������
		void QuestSystemComplete(FName _ID);

	//UI�@Bind�@QuestSystemt�ʒm
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void BindQuestSystemNotify(FName _Name);

	//UI�@Bind�@QuestSystemt�ʒm �N�G�X�g���R���v���[�g������
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void BindQuestSystemNotifyComplete(FName _Name);

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void TaskCompletionBlueprintAction(FName _ID);

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* GuardEffectCom;


};

