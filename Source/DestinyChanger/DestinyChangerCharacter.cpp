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
		//�N�G�X�g�V�X�e����UI�ɒʒm���邽�߂̃o�C���h
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
 * @brief   LightAttack�A�N�V�����̃R�[���o�b�N�ł��B
 *
 * @details �C���^���N�g�\�I�u�W�F�N�g������ꍇ�̓C���^���N�g���Ăяo���I������B
 *			����������Ă��Ȃ��ꍇ�͑������܂��B
 *          ����������Ă���ꍇ�AisAttacking�t���O�𗧂ĂčU�����J�n���A�U���R���{��1�J�E���g�A�b�v���܂��B
 *
 * @param   Value InputActionValue
 *
 * @return  �Ȃ�
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

	//����������Ă���ꍇ�͕���̐؂�ւ����s��
	if (MainWeapon) {
		if (MainWeapon->GetIsAttachToHand()) {												//����������Ă��邩�ǂ���
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && AnimInstance->Montage_IsPlaying(AnimMontage_WeaponDraw))	//����𑕔�����A�j���[�V�������Đ����Ȃ�return
				return;

			PlayAnimMontage(AnimMontage_WeaponDraw);										//�����ĂȂ��ꍇ�A����𑕔�����A�j���[�V�������Đ�	
			return;
		}
	}

	//�U�����ł͂Ȃ����̂ݍU�����s��
	if (!bIsAttacking) {
		//Attack Assist Component�Ŋp�x���C��
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
			LightAttackCountUp();	//���̍U���ɔ����ăJ�E���g�A�b�v
		}
	}

}

void ADestinyChangerCharacter::HeavyAttack(const FInputActionValue& Value)
{
	//�܂��������Ă��Ȃ��@Debug�L�[�Ƃ��Ďg�p
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
	//����������Ă���ꍇ�͕���̐؂�ւ����s��
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
 * @brief �A�N�^���ړ����邽�߂̊֐�
 * 
 * @details ���͂��ꂽ�l�ɉ����ăA�N�^���ړ����܂��B���͂�Vector2D�^�ł��B
* 
 * @param Value ���͂��ꂽ�A�N�V�����̒l
 * @return �Ȃ�
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
 * @brief ���[���A�N�V���������s���܂��B
 * 
 * @details FreeformRollComponent���g�p���āA���[���A�N�V���������s���܂��B
 * 
 * @return �Ȃ�
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
* @brief �G�̕�������������\������
* 
* @details UMG���쐬���A����������Viewport�ɒǉ�����B
* 
* @param _Target : �^�[�Q�b�g�ƂȂ�AActor*�i�@Enemy�j
* 
* @return UUserWidget* : �쐬���ꂽWidget�̃A�h���X��Ԃ��B���s����nullptr��Ԃ��B
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
 * @brief �U�����󂯂����̏���
 * 
 * @details �_���[�W���󂯂���HP�����炵�āAHP��0�ȉ��ɂȂ����玀�S�������s���܂��B�@
 *			�K�[�h����DestinySystem�𔭓����܂��A���_���[�W���󂯂閳�G���Ԃ��������܂��B
 * 
 * @param _Damage �󂯂�_���[�W��
 * 
 * @return void
 */
void ADestinyChangerCharacter::TakePlayerDamage(float _Damage)
{
	//���G��ԂȂ珈�����s��Ȃ�
	if (bIsInvincible)	return;

	//�K�[�h���̏ꍇDestinySystem�𔭓�
	if (bIsGuarding) {

		ExecuteDestinySystem();							//DestinySystem�𔭓�

		PlayAnimMontage(AnimMontage_GuardHit);			//�K�[�hHit�A�j���[�V�������Đ�

		//Effect���~�@�K�[�h��CD�ɓ���
		StopParticleSystem();
		bIsGuardGaugeCountDown = true;

	}	//�K�[�h���Ă��Ȃ����̏���
	else{
		HP -= _Damage;									//HP�����炷

		if(!bIsAttacking)
			PlayAnimMontage(AnimMontage_TakeDamage);	//�_���[�W���󂯂����̃A�j���[�V�������Đ�

		//HP��0�ȉ��ɂȂ����玀�S
		if (HP <= 0) {
			//���S����
			Death();
			return;
		}
	}

	//���G��Ԃɂ���
	bIsInvincible = true;
	//�^�C�}�[�Ŗ��G��Ԃ���������
	FTimerHandle InvincibleFlagResetTimerHandle;
	GetWorldTimerManager().SetTimer(InvincibleFlagResetTimerHandle, this, &ADestinyChangerCharacter::InvincibleFlagReset, InvincibleTime);
}

void ADestinyChangerCharacter::InvincibleFlagReset()
{
	bIsInvincible = false;
}

void ADestinyChangerCharacter::Death()
{
	//���S����
	PlayAnimMontage(AnimMontage_Death);
}

/**
 * @brief �U���͂̔{����ݒ菈��
 *
 * @details �v���C���[�̃��x���ɉ����čU���͂̔{����ݒ肵�܂��B
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
	//UI�ɒʒm
	BindQuestSystemNotifyComplete( _ID );

	//BP�Ŏ������ꂽ�C�x���g�����s
	TaskCompletionBlueprintAction( _ID );

}

/**
* @brief �K�[�h������s��
* 
* @details �v���C���[���K�[�h�{�^�������������𔻒肵�A�K�[�h��Ԃɂ���
* 
* @param Value �{�^�����͒l
* 
* @return void
*/
void ADestinyChangerCharacter::OnGuard(const FInputActionValue& Value)
{
	//CD��
	if (bIsGuardGaugeCountDown){	
		bIsGuarding = false;
		return;
	}

	//�K�[�h��Ԃɂ���
	bIsGuarding = true; 
}

void ADestinyChangerCharacter::OffGuard(const FInputActionValue& Value)
{
	//�K�[�h��Ԃ���������
	bIsGuarding = false;
}


/**
 * @brief �K�[�h�̏����֐�
 * 
 * @details �K�[�h���̓G�t�F�N�g���Đ��A�K�[�h�Q�[�W�����炵�A
 *			�K�[�h�Q�[�W��0�ɂȂ�����K�[�h��Ԃ���������B�G�t�F�N�g����~����B
 */
void ADestinyChangerCharacter::GuradFlagReset(float _DeltaTime)
{
	//1�t���[���̗��z����
	float IdealDeltaTime = 1.f / 60.f;

	//�␳�W��
	float CompensationFactor = _DeltaTime / IdealDeltaTime;

	if (bIsGuarding) {
		//�K�[�h���̏ꍇ�̓K�[�h�Q�[�W�����炷
		GuardGaugeCountDown(CompensationFactor);

		//�K�[�h���͈ړ��ł��Ȃ��悤�ɂ���
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		GetCharacterMovement()->MaxAcceleration = 400.f;

		//Effect���Đ�
		StartParticleSystem();
	}
	else {
		//�K�[�h���łȂ��ꍇ�̓K�[�h�Q�[�W�𑝂₷
		GuardGaugeCountUp(CompensationFactor);

		//�K�[�h���łȂ��ꍇ�͈ړ��ł���悤�ɂ���
		GetCharacterMovement()->MaxWalkSpeed = 800.f;
		GetCharacterMovement()->MaxAcceleration = 1500.f;

		//Effect���~
		StopParticleSystem();
	}
}

void ADestinyChangerCharacter::GuardGaugeCountUp(float _CompensationFactor)
{
	//�K�[�h�Q�[�W�𑝂₷
	fGuardGauge += 1.f * _CompensationFactor;

	//�K�[�h�Q�[�W���ő�l�𒴂�����ő�l�ɂ���
	if (fGuardGauge > fMaxGuardGauge) {
		fGuardGauge = fMaxGuardGauge;

		bIsGuardGaugeCountDown = false;
	}
}

void ADestinyChangerCharacter::GuardGaugeCountDown(float _CompensationFactor)
{
	fGuardGauge -= 2.f * _CompensationFactor;

	//�K�[�h�Q�[�W��0�ȉ��ɂȂ�����0�ɂ���
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
		GuardEffectCom->ActivateSystem();			//particle���Đ�

	}
}

void ADestinyChangerCharacter::StopParticleSystem()
{
	if (GuardEffectCom && GuardEffectCom->IsActive())
	{
		GuardEffectCom->Deactivate();			//particle���~
	}
}

void ADestinyChangerCharacter::ExecuteDestinySystem()
{
	//�U���͂�2�{�ɂ���
	MainWeapon->SetAttackPowerRatio( GetAttackPowerRatio() );

	//�U���͂�2�{�ɂ��鎞�Ԃ��v��
	CreateAttackPowerResetTimer();
}

void ADestinyChangerCharacter::AddDestinySystemTimerLength()
{
	//���̎��Ԃɒǉ����鎞�Ԃ𑫂�
	float tmp_NowTime = GetWorld()->GetTimerManager().GetTimerRemaining(DestinySystemTimerHandle);

	fDestinySystemTimerLength = tmp_NowTime > 0.f ? tmp_NowTime + fDestinySystemAddTime : fDestinySystemAddTime;

	if (fDestinySystemTimerLength > fDestinySystemTimeMax)
		fDestinySystemTimerLength = fDestinySystemTimeMax;
}

void ADestinyChangerCharacter::AttackPowerReset()
{
	//�U���͂����ɖ߂�
	MainWeapon->ResetAttackPowerRatio();
	fDestinySystemTimerLength = 0.f;

	//�^�C�}�[�����Z�b�g
	GetWorldTimerManager().ClearTimer(DestinySystemTimerHandle);
}

void ADestinyChangerCharacter::CreateAttackPowerResetTimer()
{
	AddDestinySystemTimerLength();	//�U���͂�2�{�ɂ��鎞�Ԃ��v��

	GetWorldTimerManager().SetTimer(DestinySystemTimerHandle, this, &ADestinyChangerCharacter::AttackPowerReset, fDestinySystemTimerLength);
}

void ADestinyChangerCharacter::AttackPowerRatioReset()
{
	//�U���͂̔{�����ŏ��ɖ߂�
	fAttackPowerRatio = fDefaultAttackPowerRatio;
}

float ADestinyChangerCharacter::GetAttackPowerRatio()
{
	//�U���{���������čs��
	if (fAttackPowerRatio >= 1.f)	{
		fAttackPowerRatio -= 0.1f;
	}

	return fAttackPowerRatio;
}

void ADestinyChangerCharacter::LevelUp()
{
	LevelData.fLevelUpExp = LevelData.fLevelUpExp * 1.5f;	//���̃��x���A�b�v�ɕK�v�Ȍo���l�𑝂₷

	LevelData.iLevel++;

	StatusUp();
}

/**
 * @brief ���x���A�b�v���̃X�e�[�^�X�A�b�v����
 * 
 * @details HP���㏸���A�U���͂��㏸������B
 * 
 * @return None
 */
void ADestinyChangerCharacter::StatusUp()
{
	//���x���A�b�v���̃X�e�[�^�X�A�b�v����
	//HP���㏸
	MaxHP += LevelData.iLevel * LevelData.iLevel ;

	HP = MaxHP;

	//�U���͂��㏸
	fPower += 1.f;
}

void ADestinyChangerCharacter::AddExp(float _Exp)
{
	//�o���l�����Z
	LevelData.fLevelExp += _Exp;

	//���x���A�b�v�ɕK�v�Ȍo���l�𒴂����烌�x���A�b�v
	if (LevelData.fLevelExp >= LevelData.fLevelUpExp) {
		LevelUp();
		LevelData.fLevelExp = 0.f;
	}
}




