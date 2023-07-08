//制作日：2023/07/08　制作者：トウ　更新内容：敵の基本処理

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DestinyChangerGameMode.h"

#include "EnemyBase.generated.h"

UCLASS()
class DESTINYCHANGER_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

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

protected:
	inline class ADestinyChangerGameMode* GetGameMode();
public:
	// static ADestinyChangerGameMode* GameMode;
	ADestinyChangerGameMode* GameMode;
};
