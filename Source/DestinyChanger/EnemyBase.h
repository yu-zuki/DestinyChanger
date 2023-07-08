// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Damage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Heal(float Heal);

	UFUNCTION(BlueprintCallable, Category = "HP")
		virtual void Death();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		bool bIsAttacked = false;				//çUåÇÇéÛÇØÇΩÇ©Ç«Ç§Ç©

	void ResetIsAttacked(); 

protected:
	inline class ADestinyChangerGameMode* GetGameMode();
public:
	// static ADestinyChangerGameMode* GameMode;
	ADestinyChangerGameMode* GameMode;
};
