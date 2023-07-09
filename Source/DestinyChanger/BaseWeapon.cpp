// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DestinyChangerCharacter.h"
#include "AttackAssistComponent.h"


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

void ABaseWeapon::CheckOverlap()
{
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 忽略自身
	FComponentQueryParams ComponentQueryParams;
	FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1);

	GetWorld()->ComponentOverlapMulti(Overlaps, ItemStaticMesh, ItemStaticMesh->GetComponentLocation(), ItemStaticMesh->GetComponentRotation(), ComponentQueryParams, ObjectQueryParams);

	for (const FOverlapResult& Result : Overlaps)
	{
		EnemyOnOverlap(Result.GetActor());
	}

}

void ABaseWeapon::EnemyOnOverlap(AActor* EnemyActor)
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
