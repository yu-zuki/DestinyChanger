// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "DestinyChangerGameMode.h"

//ADestinyChangerGameMode* AEnemyBase::GameMode = nullptr;	//������

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//Bind �U���󂯂��O�i�v���C���[�̍U���A�j���[�V������Play������j�Ɂ@bIsAttacked�@��false�ɂ���
	GetGameMode()->AttackEndEventBind(this, &AEnemyBase::ResetIsAttacked);
	
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
	if(bIsAttacked)		//�v���C���[�̍U���A�j�����I����Ă��Ȃ��Ƃ��̓_���[�W���󂯂Ȃ��i2��U�������̂�h���j
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

inline ADestinyChangerGameMode* AEnemyBase::GetGameMode()
{
	//�L���V���[
	if (GameMode == nullptr)	{
		//GameMode���擾
		GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode == nullptr)		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode���擾�ł��܂���ł���"));
			return nullptr;
		}
		return nullptr;
	}

	return GameMode;
}

