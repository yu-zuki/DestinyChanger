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


//////////////////////////////////////////////////////////////////////////
// ADestinyChangerCharacter

ADestinyChangerCharacter::ADestinyChangerCharacter()
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
}

void ADestinyChangerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

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

void ADestinyChangerCharacter::LightAttack(const FInputActionValue& Value)
{
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
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::LightAttack);
		//EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::LightAttack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::HeavyAttack);

		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::ToggleCombat);

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::Roll);
	}

}

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

void ADestinyChangerCharacter::Roll(const FInputActionValue& Value)
{
	FreeformRollComponent->RollProcess();
	bIsAttacking = false;
}

UAttackAssistComponent* ADestinyChangerCharacter::GetAttackAssistComponent() const
{
	return AttackAssistComponent;
}

//////////////////////////////////////////////////////////////////////////
// Show Enemy Targeting
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




