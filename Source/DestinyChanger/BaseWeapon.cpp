// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"

#include "DestinyChangerCharacter.h"
#include "AttackAssistComponent.h"
#include "Engine/World.h"


ABaseWeapon::ABaseWeapon()
{
	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(ItemStaticMesh);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::AttachToHand()
{
	AttachActor(HandSocketName);
	bIsAttachToHand = false;
}

void ABaseWeapon::DetachFromHand()
{
	AttachActor( AttachSocketName );
	bIsAttachToHand = true;
}

void ABaseWeapon::OnEquipped()
{
	Super::OnEquipped();
}

void ABaseWeapon::OnUnequipped()
{
	Super::OnUnequipped();

}

//チェック
void ABaseWeapon::CheckOverlap()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector Start = WeaponCollision->GetComponentLocation();
	FVector End = Start;// + GetActorForwardVector() * 100.0f;
	FQuat Rot = WeaponCollision->GetComponentQuat();			// 
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(WeaponCollision->GetScaledCapsuleRadius(), WeaponCollision->GetScaledCapsuleHalfHeight());

	bool isHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, Rot, ECollisionChannel::ECC_GameTraceChannel1, CollisionShape, CollisionParams);
	
	//if (isHit != true) { return; }

	if (false)	{
		DrawDebugCapsule(GetWorld(), (Start + End) / 2,
			CollisionShape.GetCapsuleHalfHeight(),
			CollisionShape.GetCapsuleRadius(), Rot, FColor::Red, true, -1.0f, 0, 1.0f);
	}

	for (FHitResult HitResult : HitResults)	{
		EnemyOnOverlap(HitResult);
	}
}

void ABaseWeapon::EnemyOnOverlap(FHitResult& _HitResult)
{
	//Cast
	AEnemyBase* Enemy = Cast<AEnemyBase>(_HitResult.GetActor());
	if (Enemy) {
		if (Enemy->bIsAttacked) {
			return;
		}

		Enemy->Damage(fDamage);						//敵にダメージを与える
		FVector Center = _HitResult.Location;	//ヒットエフェクトの位置

		AActor* Player = GetOwner();			//プレイヤーのヒットストップ処理
		if (Player) {
			ADestinyChangerCharacter* DestinyChangerCharacter = Cast<ADestinyChangerCharacter>(Player);
			if (DestinyChangerCharacter) {
				DestinyChangerCharacter->GetAttackAssistComponent()->HitStop();
			}
		}

		//Debug
		FQuat Rotation = FQuat::Identity;
		FVector Extent = FVector(5, 5, 5);

		DrawDebugBox(GetWorld(), Center, Extent, Rotation, FColor::Green, false, 5.0f, 0, 1.0f);
		//Enemyの名前とHPをPrintStringで表示
		FString OutputString = FString::Printf(TEXT("Enemy: %s, Health: %f"), *Enemy->GetName(), Enemy->GetHP());
		UKismetSystemLibrary::PrintString(this, OutputString);
	}
}

//破棄
void ABaseWeapon::EnemyOnOverlap(AActor* EnemyActor,FVector HitLocation)
{
	//Cast
	AEnemyBase* Enemy = Cast<AEnemyBase>(EnemyActor);
	if (Enemy)	{
		if (Enemy->bIsAttacked) {
			return;
		}

		Enemy->Damage(10);

		//HitStop
		AActor* Player = GetOwner();
		if (Player) {
			ADestinyChangerCharacter* DestinyChangerCharacter = Cast<ADestinyChangerCharacter>(Player);
			if (DestinyChangerCharacter) {
				DestinyChangerCharacter->GetAttackAssistComponent()->HitStop();
			}
		}

		//使用KismetSystemLibrary::PrintString()打印Enemy的名字与血量
		FString OutputString = FString::Printf(TEXT("Enemy: %s, Health: %f"), *Enemy->GetName(), Enemy->GetHP());
		UKismetSystemLibrary::PrintString(this, OutputString);
	}
}
