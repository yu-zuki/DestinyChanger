// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEquippable.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API ABaseWeapon : public ABaseEquippable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		FName HandSocketName;	//�������̃A�^�b�`��

	bool bIsAttached;	//��ɑ������邩�H

public:
	UFUNCTION(BlueprintPure, Category = "Weapon")
		FName GetHandSocketName() const { return HandSocketName; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetHandSocketName(FName NewSocketName) { HandSocketName = NewSocketName; }

	bool GetIsAttached() const { return bIsAttached; }
	void SetIsAttached(bool bNewIsAttached) { bIsAttached = bNewIsAttached; }

	virtual void OnEquipped() override;
};
