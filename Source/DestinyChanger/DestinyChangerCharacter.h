//制作日：2023/07/08　制作者：トウ　処理内容：プレイヤーの処理
//制作日：2023/07/08　制作者：トウ　更新内容：攻撃モーションの追加
//更新日：2023/07/09　更新者：トウ　更新内容：攻撃コンボの追加
//更新日：2023/07/09　更新者：トウ　更新内容：回避アクションの追加


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

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

//new

//////////////
//攻撃処理
public:
	//攻撃のフラグ
	bool bIsAttacking;

protected:
	//軽い攻撃の入力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* LightAttackAction;

	//重い攻撃の入力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* HeavyAttackAction;

	//入力アクションの処理
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);

	//攻撃のモーション1,2,3,4
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
//武器処理
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABaseWeapon> MainWeaponClass;	// プレイヤーのメイン武器のクラス

	class ABaseWeapon* MainWeapon;	// プレイヤーのメイン武器

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_WeaponDraw;	    // 武器を構えるモーション

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_WeaponDisarm;	// 武器をしまうモーション

	void ToggleCombat(const FInputActionValue& Value);	// 戦闘モードの切り替え

	//重い攻撃の入力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle")
		class UInputAction* ToggleCombatAction;

	UFUNCTION(BlueprintCallable, Category = "Battle")
		void SetMainWeapon(ABaseWeapon* _Weapon);
	UFUNCTION(BlueprintCallable, Category = "Battle")
		ABaseWeapon* GetMainWeapon() const;

//////////////
//回避処理
protected:
	//回避の入力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UInputAction* RollAction;

	//回避の処理
	void Roll(const FInputActionValue& Value);

public:
	UAttackAssistComponent* GetAttackAssistComponent() const;

//////////////
//EnemyDirectionIndicator
public:
	class UUserWidget* ShowEnemyDirectionIndicator(AActor * _Target);
	UArrowComponent* GetEnemyDirectionIndicator() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UEnemyTargeting> EnemyTargeting_UMG;	// プレイヤーのメイン武器のクラス

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* EnemyDirectionIndicator;

//////////////
//ダメージ受け処理
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_TakeDamage;	// ダメージを受けるモーション
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_Death;		// 死亡モーション

	void TakePlayerDamage(float _Damage);	// ダメージを受ける

	bool bIsInvincible;							// 無敵状態かどうか
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float InvincibleTime;						// 無敵状態の時間

	void InvincibleFlagReset();					// 無敵状態を解除する

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	void Death();

	//％を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHPPercent() { return HP / MaxHP;}

//////////////////////////////////////////////////////////////////////////
//防御処理
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
	
	//％を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetGuardGaugePercent();

	// 防御中Hitモーション
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AnimMontage_GuardHit;		

	UFUNCTION(BlueprintCallable)
		void StartParticleSystem();

	UFUNCTION(BlueprintCallable)
		void StopParticleSystem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle", meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* GuardEffectCom;


};

