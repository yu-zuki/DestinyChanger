// Copyright Epic Games, Inc. All Rights Reserved.

#include "DestinyChangerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"
#include "AttackAssistComponent.h"
#include "FreeformRollComponent.h"
#include "BaseWeapon.h"
#include "EnemyTargeting.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"
#include "InteractComponent.h"
#include "DialogueManager.h"
#include "Dialogue_UMG.h"
#include "InteractableAPI.h"
#include "QuestSystem.h"
#include "DestinyChangerGameMode.h"
#include "QuestGiverComponent.h"




//////////////////////////////////////////////////////////////////////////
// ADestinyChangerCharacter

ADestinyChangerCharacter::ADestinyChangerCharacter()
	:bIsInvincible(false), InvincibleTime(1.f), HP(100.f),MaxHP(100.f),
	 fGuardGauge(120.f), fMaxGuardGauge(120.f),
	 fDestinySystemAddTime(5.f), fDestinySystemTimeMax(15.f), fDestinySystemTimerLength(0.f)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	EnemyDirectionIndicator = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemyDirectionIndicator"));
	EnemyDirectionIndicator->SetupAttachment(FollowCamera);

	//Player Attack Assist Component
	FreeformRollComponent = CreateDefaultSubobject<UFreeformRollComponent>(TEXT("FreeformRoll"));
	AttackAssistComponent = CreateDefaultSubobject<UAttackAssistComponent>(TEXT("AttackAssist"));

	//GuardEffectCom
	GuardEffectCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	GuardEffectCom->SetupAttachment(RootComponent);

	//InteractComponent
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));

	//QuestComponent
	QuestSystemComponent = CreateDefaultSubobject<UQuestSystem>(TEXT("QuestComponent"));

	//QuestGiverComponent
	QuestGiverrComponent = CreateDefaultSubobject<UQuestGiverComponent>(TEXT("QuestGiverComponent"));


}

void ADestinyChangerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (QuestSystemComponent != nullptr) {
		//クエストシステムがUIに通知するためのバインド
		QuestSystemComponent->BindUINotifyExecutingQuest(this, &ADestinyChangerCharacter::BindQuestSystemNotify);
		QuestSystemComponent->BindNotifyExecutingQuestComplete(this, &ADestinyChangerCharacter::QuestSystemComplete);
	}

	//Attack Power Ratio Init
	fAttackPowerRatio = fDefaultAttackPowerRatio;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Spawn Main Weapon
	if (MainWeaponClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		MainWeapon = GetWorld()->SpawnActor<ABaseWeapon>(MainWeaponClass, SpawnParams);
		if (MainWeapon) {
			SetMainWeapon(MainWeapon);
			MainWeapon->OnEquipped();
		}
	}
}

void ADestinyChangerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GuradFlagReset(DeltaTime);
}

/**
 * @brief   LightAttackアクションのコールバックです。
 *
 * @details インタラクト可能オブジェクトがある場合はインタラクトを呼び出し終了する。
 *			武器を持っていない場合は装備します。
 *          武器を持っている場合、isAttackingフラグを立てて攻撃を開始し、攻撃コンボを1つカウントアップします。
 *
 * @param   Value InputActionValue
 *
 * @return  なし
 */
void ADestinyChangerCharacter::LightAttack(const FInputActionValue& Value)
{
	if (AActor* InteraObj = InteractComponent->GetInteractObject()) {
		//Cast
		if (IInteractableAPI* InteractableObject = Cast<IInteractableAPI>(InteraObj)) {
			InteractableObject->Interact(this);
			return;
		}
	}

	//武器を持っている場合は武器の切り替えを行う
	if (MainWeapon) {
		if (MainWeapon->GetIsAttachToHand()) {												//武器を持っているかどうか
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && AnimInstance->Montage_IsPlaying(AnimMontage_WeaponDraw))	//武器を装備するアニメーションを再生中ならreturn
				return;

			PlayAnimMontage(AnimMontage_WeaponDraw);										//持ってない場合、武器を装備するアニメーションを再生	
			return;
		}
	}

	//攻撃中ではない時のみ攻撃を行う
	if (!bIsAttacking) {
		//Attack Assist Componentで角度を修正
		AttackAssistComponent->CorrectAttackAngle();

		//play light attack animation
		if (LightAttackMontageOne && LightAttackMontageTwo && LightAttackMontageThree && LightAttackMontageFour) {
			switch (eAttackComb)
			{
			case EAttackComb::LightAttackOne:
				PlayAnimMontage(LightAttackMontageOne);
				break;
			case EAttackComb::LightAttackTwo:
				PlayAnimMontage(LightAttackMontageTwo);
				break;
			case EAttackComb::LightAttackThree:
				PlayAnimMontage(LightAttackMontageThree);
				break;
			case EAttackComb::LightAttackFour:
				PlayAnimMontage(LightAttackMontageFour);
				break;
			}		

			bIsAttacking = true;	//set attacking to true
			LightAttackCountUp();	//次の攻撃に備えてカウントアップ
		}
	}

}

void ADestinyChangerCharacter::HeavyAttack(const FInputActionValue& Value)
{
	//まだ実装していない　Debugキーとして使用
	UGameplayStatics::OpenLevel(GetWorld(), FName( *UGameplayStatics::GetCurrentLevelName( GetWorld() ) ) );
}

void ADestinyChangerCharacter::LightAttackCountUp()
{
	switch (eAttackComb)
	{
	case EAttackComb::LightAttackOne:
		eAttackComb = EAttackComb::LightAttackTwo;
		break;
	case EAttackComb::LightAttackTwo:
		eAttackComb = EAttackComb::LightAttackThree;
		break;
	case EAttackComb::LightAttackThree:
		eAttackComb = EAttackComb::LightAttackFour;
		break;
	case EAttackComb::LightAttackFour:
		eAttackComb = EAttackComb::LightAttackOne;
		break;
	}
}

void ADestinyChangerCharacter::HitDecect()
{
	//hit detect
	MainWeapon->CheckOverlap();
}

void ADestinyChangerCharacter::ToggleCombat(const FInputActionValue& Value)
{
	//武器を持っている場合は武器の切り替えを行う
	if (MainWeapon) {
		(MainWeapon->GetIsAttachToHand()) ? PlayAnimMontage(AnimMontage_WeaponDraw) : PlayAnimMontage(AnimMontage_WeaponDisarm);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADestinyChangerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::Look);

		//Attacking
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::LightAttack);
		//EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::LightAttack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::HeavyAttack);

		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::ToggleCombat);

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::Roll);

		//Guarding
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::OnGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &ADestinyChangerCharacter::OffGuard);
	}

}

/**
 * @brief アクタを移動するための関数
 * 
 * @details 入力された値に応じてアクタを移動します。入力はVector2D型です。
* 
 * @param Value 入力されたアクションの値
 * @return なし
 */
void ADestinyChangerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADestinyChangerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADestinyChangerCharacter::SetMainWeapon(ABaseWeapon* _Weapon)
{
	MainWeapon = _Weapon;
}

ABaseWeapon* ADestinyChangerCharacter::GetMainWeapon() const
{
	return MainWeapon;
}

/**
 * @brief ロールアクションを実行します。
 * 
 * @details FreeformRollComponentを使用して、ロールアクションを実行します。
 * 
 * @return なし
 */
void ADestinyChangerCharacter::Roll(const FInputActionValue& Value)
{
	FreeformRollComponent->RollProcess();
	bIsAttacking = false;
}

UAttackAssistComponent* ADestinyChangerCharacter::GetAttackAssistComponent() const
{
	return AttackAssistComponent;
}

/**
* @brief 敵の方向を示す矢印を表示する
* 
* @details UMGを作成し、初期化してViewportに追加する。
* 
* @param _Target : ターゲットとなるAActor*（　Enemy）
* 
* @return UUserWidget* : 作成されたWidgetのアドレスを返す。失敗時はnullptrを返す。
*/
UUserWidget* ADestinyChangerCharacter::ShowEnemyDirectionIndicator(AActor* _Target)
{
	//Create Widget
	if (EnemyTargeting_UMG) {
		UEnemyTargeting* tmp_UMG = CreateWidget<UEnemyTargeting>(GetWorld(), EnemyTargeting_UMG);

		//Init
		tmp_UMG->Init(_Target, EnemyDirectionIndicator);

		//Add to Viewport
		tmp_UMG->AddToViewport();

		return tmp_UMG;
	}

	return nullptr;
}

UArrowComponent* ADestinyChangerCharacter::GetEnemyDirectionIndicator() const
{
	return EnemyDirectionIndicator;
}

/**
 * @brief 攻撃を受けた時の処理
 * 
 * @details ダメージを受けた時HPを減らして、HPが0以下になったら死亡処理を行います。　
 *			ガード中はDestinySystemを発動します、一回ダメージを受ける無敵時間が発生します。
 * 
 * @param _Damage 受けるダメージ量
 * 
 * @return void
 */
void ADestinyChangerCharacter::TakePlayerDamage(float _Damage)
{
	//無敵状態なら処理を行わない
	if (bIsInvincible)	return;

	//ガード中の場合DestinySystemを発動
	if (bIsGuarding) {

		ExecuteDestinySystem();							//DestinySystemを発動

		PlayAnimMontage(AnimMontage_GuardHit);			//ガードHitアニメーションを再生

		//Effectを停止　ガードのCDに入る
		StopParticleSystem();
		bIsGuardGaugeCountDown = true;

	}	//ガードしていない時の処理
	else{
		HP -= _Damage;									//HPを減らす

		if(!bIsAttacking)
			PlayAnimMontage(AnimMontage_TakeDamage);	//ダメージを受けた時のアニメーションを再生

		//HPが0以下になったら死亡
		if (HP <= 0) {
			//死亡処理
			Death();
			return;
		}
	}

	//無敵状態にする
	bIsInvincible = true;
	//タイマーで無敵状態を解除する
	FTimerHandle InvincibleFlagResetTimerHandle;
	GetWorldTimerManager().SetTimer(InvincibleFlagResetTimerHandle, this, &ADestinyChangerCharacter::InvincibleFlagReset, InvincibleTime);
}

void ADestinyChangerCharacter::InvincibleFlagReset()
{
	bIsInvincible = false;
}

void ADestinyChangerCharacter::Death()
{
	//死亡処理
	PlayAnimMontage(AnimMontage_Death);
}

/**
 * @brief 攻撃力の倍率を設定処理
 *
 * @details プレイヤーのレベルに応じて攻撃力の倍率を設定します。
 *
 * @return void
 */
float ADestinyChangerCharacter::GetAttackPower()
{
	return MainWeapon->GetAttackPower() * fPower;
}


float ADestinyChangerCharacter::GetDestinySystemTime()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(DestinySystemTimerHandle);
}

void ADestinyChangerCharacter::QuestSystemComplete(FName _ID)
{
	//UIに通知
	BindQuestSystemNotifyComplete( _ID );

	//BPで実装されたイベントを実行
	TaskCompletionBlueprintAction( _ID );

}

/**
* @brief ガード判定を行う
* 
* @details プレイヤーがガードボタンを押したかを判定し、ガード状態にする
* 
* @param Value ボタン入力値
* 
* @return void
*/
void ADestinyChangerCharacter::OnGuard(const FInputActionValue& Value)
{
	//CD中
	if (bIsGuardGaugeCountDown){	
		bIsGuarding = false;
		return;
	}

	//ガード状態にする
	bIsGuarding = true; 
}

void ADestinyChangerCharacter::OffGuard(const FInputActionValue& Value)
{
	//ガード状態を解除する
	bIsGuarding = false;
}


/**
 * @brief ガードの処理関数
 * 
 * @details ガード中はエフェクトを再生、ガードゲージを減らし、
 *			ガードゲージが0になったらガード状態を解除する。エフェクトも停止する。
 */
void ADestinyChangerCharacter::GuradFlagReset(float _DeltaTime)
{
	//1フレームの理想時間
	float IdealDeltaTime = 1.f / 60.f;

	//補正係数
	float CompensationFactor = _DeltaTime / IdealDeltaTime;

	if (bIsGuarding) {
		//ガード中の場合はガードゲージを減らす
		GuardGaugeCountDown(CompensationFactor);

		//ガード中は移動できないようにする
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		GetCharacterMovement()->MaxAcceleration = 400.f;

		//Effectを再生
		StartParticleSystem();
	}
	else {
		//ガード中でない場合はガードゲージを増やす
		GuardGaugeCountUp(CompensationFactor);

		//ガード中でない場合は移動できるようにする
		GetCharacterMovement()->MaxWalkSpeed = 800.f;
		GetCharacterMovement()->MaxAcceleration = 1500.f;

		//Effectを停止
		StopParticleSystem();
	}
}

void ADestinyChangerCharacter::GuardGaugeCountUp(float _CompensationFactor)
{
	//ガードゲージを増やす
	fGuardGauge += 1.f * _CompensationFactor;

	//ガードゲージが最大値を超えたら最大値にする
	if (fGuardGauge > fMaxGuardGauge) {
		fGuardGauge = fMaxGuardGauge;

		bIsGuardGaugeCountDown = false;
	}
}

void ADestinyChangerCharacter::GuardGaugeCountDown(float _CompensationFactor)
{
	fGuardGauge -= 2.f * _CompensationFactor;

	//ガードゲージが0以下になったら0にする
	if (fGuardGauge < 0.f) {
		fGuardGauge = 0.f;

		bIsGuardGaugeCountDown = true;
	}
}

float ADestinyChangerCharacter::GetGuardGaugePercent()
{
	return fGuardGauge / fMaxGuardGauge;
}

void ADestinyChangerCharacter::StartParticleSystem()
{
	if (GuardEffectCom && !GuardEffectCom->IsActive())	{
		GuardEffectCom->ActivateSystem();			//particleを再生

	}
}

void ADestinyChangerCharacter::StopParticleSystem()
{
	if (GuardEffectCom && GuardEffectCom->IsActive())
	{
		GuardEffectCom->Deactivate();			//particleを停止
	}
}

void ADestinyChangerCharacter::ExecuteDestinySystem()
{
	//攻撃力を2倍にする
	MainWeapon->SetAttackPowerRatio( GetAttackPowerRatio() );

	//攻撃力を2倍にする時間を計測
	CreateAttackPowerResetTimer();
}

void ADestinyChangerCharacter::AddDestinySystemTimerLength()
{
	//今の時間に追加する時間を足す
	float tmp_NowTime = GetWorld()->GetTimerManager().GetTimerRemaining(DestinySystemTimerHandle);

	fDestinySystemTimerLength = tmp_NowTime > 0.f ? tmp_NowTime + fDestinySystemAddTime : fDestinySystemAddTime;

	if (fDestinySystemTimerLength > fDestinySystemTimeMax)
		fDestinySystemTimerLength = fDestinySystemTimeMax;
}

void ADestinyChangerCharacter::AttackPowerReset()
{
	//攻撃力を元に戻す
	MainWeapon->ResetAttackPowerRatio();
	fDestinySystemTimerLength = 0.f;

	//タイマーをリセット
	GetWorldTimerManager().ClearTimer(DestinySystemTimerHandle);
}

void ADestinyChangerCharacter::CreateAttackPowerResetTimer()
{
	AddDestinySystemTimerLength();	//攻撃力を2倍にする時間を計測

	GetWorldTimerManager().SetTimer(DestinySystemTimerHandle, this, &ADestinyChangerCharacter::AttackPowerReset, fDestinySystemTimerLength);
}

void ADestinyChangerCharacter::AttackPowerRatioReset()
{
	//攻撃力の倍率を最初に戻す
	fAttackPowerRatio = fDefaultAttackPowerRatio;
}

float ADestinyChangerCharacter::GetAttackPowerRatio()
{
	//攻撃倍率を減って行く
	if (fAttackPowerRatio >= 1.f)	{
		fAttackPowerRatio -= 0.1f;
	}

	return fAttackPowerRatio;
}

void ADestinyChangerCharacter::LevelUp()
{
	LevelData.fLevelUpExp = LevelData.fLevelUpExp * 1.5f;	//次のレベルアップに必要な経験値を増やす

	LevelData.iLevel++;

	StatusUp();
}

/**
 * @brief レベルアップ時のステータスアップ処理
 * 
 * @details HPを上昇し、攻撃力を上昇させる。
 * 
 * @return None
 */
void ADestinyChangerCharacter::StatusUp()
{
	//レベルアップ時のステータスアップ処理
	//HPを上昇
	MaxHP += LevelData.iLevel * LevelData.iLevel ;

	HP = MaxHP;

	//攻撃力を上昇
	fPower += 1.f;
}

void ADestinyChangerCharacter::AddExp(float _Exp)
{
	//経験値を加算
	LevelData.fLevelExp += _Exp;

	//レベルアップに必要な経験値を超えたらレベルアップ
	if (LevelData.fLevelExp >= LevelData.fLevelUpExp) {
		LevelUp();
		LevelData.fLevelExp = 0.f;
	}
}




