// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Attacking_AN.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UAttacking_AN : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTick(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference
	) override;
};
