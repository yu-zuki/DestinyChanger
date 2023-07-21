//制作日：2023/07/08　制作者：トウ　処理内容：敵の処理
//制作日：2023/07/08　制作者：トウ　更新内容：敵の基本処理

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DestinyChangerGameMode.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

#include "EnemyBase.generated.h"

UCLASS()
class DESTINYCHANGER_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	//tick
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

//////////
///Anime
public:

	//ダメージ受けた時のアニメーション
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackedAnimMontage;

	//死亡時のアニメーション
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* DeathAnimMontage;

	//攻撃時のアニメーション
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackAnimMontage;

//////////
///HP
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float MaxHP = 100.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Damage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Heal(float Heal);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Death();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		bool bIsAttacked = false;				//攻撃を受けたかどうか

	void ResetIsAttacked(); 

	//GetHP
	UFUNCTION(BlueprintCallable, Category = "HP")
		float GetHP() { return HP; }

//////////////////////////////////////////////////////////////////////////
///UI
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UBase_WidgetComponent* EnemyWidget;

		class UUserWidget* EnemyDirectionIndicator;		//Enemyの方向を示すUI

//////////////////////////////////////////////////////////////////////////
///AI
public:

	FVector StartLocation;		//初期位置

//////////////////////////////////////////////////////////////////////////
///攻撃
	float AttackDamage = 10.0f;		//攻撃力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class UCapsuleComponent* AttackCollisionComponent;	//攻撃の当たり判定

	virtual void HitDecect();

	virtual void CheckOverlap(class UCapsuleComponent* _AttackCollision);
//////////
///取得
protected:
	inline class ADestinyChangerGameMode* GetGameMode();
public:
	// static ADestinyChangerGameMode* GameMode;
	ADestinyChangerGameMode* GameMode;
};
