// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEquippable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ABaseEquippable::ABaseEquippable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(RootComponent);

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseEquippable::BeginPlay()
{
	Super::BeginPlay();

	//コリジョンをプレイヤーに無効化
	if (ItemSkeletalMesh) ItemSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (ItemStaticMesh) ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called every frame
void ABaseEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABaseEquippable::GetItemMesh() const
{
	UPrimitiveComponent* ItemMesh = Cast<UPrimitiveComponent>(ItemStaticMesh);
	if (ItemMesh)
	{
		return ItemMesh;
	}
	else
	{
		return ItemSkeletalMesh;
	}
}

void ABaseEquippable::OnEquipped()
{
	bIsEquipped = true;

	AttachActor(AttachSocketName);		//Attach to the actor mesh
}

void ABaseEquippable::OnUnequipped()
{
	bIsEquipped = false;
}

void ABaseEquippable::AttachActor(FName& _s_name)
{
	ACharacter* chara = Cast<ACharacter>(GetOwner());
	if (chara) {
		UMeshComponent* Mesh = chara->GetMesh();
		if (Mesh)		{
			//第一引数Mesh	//第二引数アタッチルール	//第三引数アタッチ先のソケット名
			RootComponent->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, _s_name);
		}
		else		{
			UE_LOG(LogTemp, Error, TEXT("AttachToComponent Is Not Found"));
		}

	}

}


