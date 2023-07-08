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

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
