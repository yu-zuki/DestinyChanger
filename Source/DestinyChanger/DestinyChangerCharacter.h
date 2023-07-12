//������F2023/07/08�@����ҁF�g�E�@�������e�F�v���C���[�̏���
//������F2023/07/08�@����ҁF�g�E�@�X�V���e�F�U�����[�V�����̒ǉ�
//�X�V���F2023/07/09�@�X�V�ҁF�g�E�@�X�V���e�F�U���R���{�̒ǉ�
//�X�V���F2023/07/09�@�X�V�ҁF�g�E�@�X�V���e�F����A�N�V�����̒ǉ�


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "DestinyChangerCharacter.generated.h"

enum class EAttackComb : uint8
{
	LightAttackNone,
	LightAttackOne,
	LightAttackTwo,
	LightAttackThree,
	LightAttackFour,
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
//EnemyDirectionIndicator
public:
	void ShowEnemyDirectionIndicator(AActor* _Target);
	UArrowComponent* GetEnemyDirectionIndicator() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UEnemyTargeting> EnemyTargeting_UMG;	// �v���C���[�̃��C������̃N���X

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* EnemyDirectionIndicator;

};

