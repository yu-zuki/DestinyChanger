// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Base_WidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UBase_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, 
	FActorComponentTickFunction *ThisTickFunction) override;

	//BeginPlay

//////////
///UI
protected:

/////////////////////////////
//		機能

	//向きをプレイヤーの方向に向ける
	void LookAtPlayer();

	//Flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
		bool bIsLookAtPlayer = false;

public:
	//Set HP
	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetHPInfo(float HP, float MaxHP);
};
