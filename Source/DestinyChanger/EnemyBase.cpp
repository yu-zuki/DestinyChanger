// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "DestinyChangerGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


//ADestinyChangerGameMode* AEnemyBase::GameMode = nullptr;	//初期化

// Sets default values
AEnemyBase::AEnemyBase()
	:HP(100.f), MaxHP(100.f), bIsAttacked(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create UCapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	//Create UStaticMeshComponent
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
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

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::Damage(float Damage)
{
	if(bIsAttacked)		//プレイヤーの攻撃アニメが終わっていないときはダメージを受けない（2回攻撃されるのを防ぐ）
		return;

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
	if (true) {

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

