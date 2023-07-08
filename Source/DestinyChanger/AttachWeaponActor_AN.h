// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttachWeaponActor_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttachWeaponActor_AN : public UAnimNotify
{
	GENERATED_BODY()
	
	UAttachWeaponActor_AN();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		bool bIsAttachToHand;	//éËÇ…ëïîıÇ∑ÇÈÇ©ÅH

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UFUNCTION(BlueprintPure, Category = "Attachment")
		bool GetIsAttachToHand() const { return bIsAttachToHand; }

	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void SetIsAttachToHand(bool bNewAttachToHand) { bIsAttachToHand = bNewAttachToHand; }
	
};
