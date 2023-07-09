// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "DestinyChangerGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


//ADestinyChangerGameMode* AEnemyBase::GameMode = nullptr;	//初期化

// Sets default values
AEnemyBase::AEnemyBase()
	:HP(100.f), MaxHP(100.f), bIsAttacked(false)
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

 //	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//Bind 攻撃受けれる前（プレイヤーの攻撃アニメーションがPlayしたら）に　bIsAttacked　をfalseにする
	GetGameMode()->AttackEndEventBind(this, &AEnemyBase::ResetIsAttacked);
	
}

void AEnemyBase::BeginDestroy()
{

	Super::BeginDestroy();

	//GetGameMode()->AttackEndEventUnBind(this, &AEnemyBase::ResetIsAttacked);
	//UnBind
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::Damage(float Damage)
{
	if(bIsAttacked)		//プレイヤーの攻撃アニメが終わっていないときはダメージを受けない（2回攻撃されるのを防ぐ）
		return;

	if(AttackedAnimMontage)		//攻撃アニメーションがあるときはそれを再生
		PlayAnimMontage(AttackedAnimMontage);

	//HitStop

	HP -= Damage;		//HP = HP - Damage
	if (HP <= 0)	{
		Death();
	}
	bIsAttacked = true;
}

void AEnemyBase::Heal(float Heal)
{
	HP += Heal;
	if (HP > MaxHP)	{
		HP = MaxHP;
	}
}

void AEnemyBase::Death()
{
	Destroy();
}

void AEnemyBase::ResetIsAttacked()
{ 
	bIsAttacked = false;

	//Debug
	if (false) {

		AActor* MyActor = this;

		// 获取 MyActor 的 UniqueID 和名称
		int32 UniqueID = MyActor->GetUniqueID();
		FString Name = MyActor->GetName();

		// 使用 FString::Printf 函数格式化输出字符串
		FString OutputString = FString::Printf(TEXT("UniqueID: %d, Name: %s"), UniqueID, *Name);

		// 将格式化后的字符串输出到屏幕上
		UKismetSystemLibrary::PrintString(this, OutputString);
	}
}

inline ADestinyChangerGameMode* AEnemyBase::GetGameMode()
{
	//キャシュー
	if (GameMode == nullptr)	{
		//GameModeを取得
		GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode == nullptr)		{
			UE_LOG(LogTemp, Warning, TEXT("GameModeが取得できませんでした"));
			return nullptr;
		}
		return GameMode;
	}

	return GameMode;
}

