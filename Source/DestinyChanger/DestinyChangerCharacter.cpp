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

#include "BaseWeapon.h"


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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
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
}

void ADestinyChangerCharacter::LightAttack(const FInputActionValue& Value)
{
	if (!bIsAttacking) {
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
}

void ADestinyChangerCharacter::ToggleCombat(const FInputActionValue& Value)
{
	//武器を持っている場合は武器の切り替えを行う
	if (MainWeapon)
	{
		if (!MainWeapon->GetIsAttached()) {
			PlayAnimMontage(AnimMontage_WeaponDraw);
			MainWeapon->SetIsAttached(true);
		}
		else
		{
			PlayAnimMontage(AnimMontage_WeaponDisarm);
			MainWeapon->SetIsAttached(false);
		}
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
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ADestinyChangerCharacter::HeavyAttack);

		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &ADestinyChangerCharacter::ToggleCombat);

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




