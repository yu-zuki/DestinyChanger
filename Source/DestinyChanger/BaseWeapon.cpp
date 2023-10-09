//制作日：2023/07/08　制作者：トウ　処理内容：武器の処理
//制作日：2023/07/09　制作者：トウ　更新内容：HitStop、HitEffect、Damgeの処理を追加

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

	//値の初期化
	fDefaultAttackPower = fAttackPower;
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

//チェック　当たり判定用のコリジョンを生成
void ABaseWeapon::CheckOverlap()
{
	TArray<FHitResult> HitResults;				//ヒットしたものを格納する配列
	FCollisionQueryParams CollisionParams;	
	CollisionParams.AddIgnoredActor(this);		//自分自身を無視する

	FVector Start = WeaponCollision->GetComponentLocation();	//生成したコリジョンの中心位置
	FVector End = Start;// + GetActorForwardVector() * 100.0f;　
	FQuat Rot = WeaponCollision->GetComponentQuat();			//生成したコリジョンの向き

	//コリジョンの形状を取得（　武器クラスで作ったカプセルコンポーネントから　）
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(WeaponCollision->GetScaledCapsuleRadius(), WeaponCollision->GetScaledCapsuleHalfHeight());


	//当たり判定を行う、ヒットしたものをHitResultsに格納
	bool isHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, Rot, ECollisionChannel::ECC_GameTraceChannel1, CollisionShape, CollisionParams);
	
	//if (isHit != true) { return; }

	//Debug
	if (false)	{
		DrawDebugCapsule(GetWorld(), (Start + End) / 2,
			CollisionShape.GetCapsuleHalfHeight(),
			CollisionShape.GetCapsuleRadius(), Rot, FColor::Red, true, -1.0f, 0, 1.0f);
	}

	//HitResultsに格納されたものを一つずつ処理
	for (FHitResult HitResult : HitResults)	{
		EnemyOnOverlap(HitResult);
	}
}

//敵との当たり判定
void ABaseWeapon::EnemyOnOverlap(FHitResult& _HitResult)
{
	//Cast
	AEnemyBase* Enemy = Cast<AEnemyBase>(_HitResult.GetActor());
	if (Enemy) {
		if (Enemy->bIsAttacked) {
			return;
		}

		AActor* Player = GetOwner();			
		if (Player) {
			ADestinyChangerCharacter* DestinyChangerCharacter = Cast<ADestinyChangerCharacter>(Player);

			/////////////////////////////////////////
			//敵にダメージを与える
			Enemy->Damage(fAttackPower * DestinyChangerCharacter->GetPower());


			/////////////////////////////////////////
			//プレイヤーのヒットストップ処理
			FVector HitLocation = _HitResult.Location;		//ヒットエフェクトの位置

			if (DestinyChangerCharacter) {
				DestinyChangerCharacter->GetAttackAssistComponent()->HitStop();
				DestinyChangerCharacter->GetAttackAssistComponent()->HitEffect(HitEffect,HitLocation,GetActorForwardVector());
			}
		}
		//Debug
		FQuat Rotation = FQuat::Identity;
		FVector Extent = FVector(5, 5, 5);

		//DrawDebugBox(GetWorld(), HitLocation, Extent, Rotation, FColor::Green, false, 5.0f, 0, 1.0f);
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

		//Playerを取得


		float Damage = fAttackPower;
		Enemy->Damage(Damage);							//敵にダメージを与える

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

void ABaseWeapon::SetAttackPowerRatio(float _DamageRatio)
{
	fAttackPower = fAttackPower * _DamageRatio;

	//0未満になったら
	if (fAttackPower < 0) {
		fAttackPower = 0;
	}
	//floatの限界を超えたら
	else if (fAttackPower > std::numeric_limits<float>::max()) {
		fAttackPower = std::numeric_limits<float>::max();
	}

	//Debug
	FString OutputString = FString::Printf(TEXT("Damage: %f"), fAttackPower);
	UKismetSystemLibrary::PrintString(this, OutputString);
}
