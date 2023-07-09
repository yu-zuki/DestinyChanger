// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackAssistComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UAttackAssistComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackAssistComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, Category = "Attack Assist")
		TSubclassOf<AActor> EnemyBaseClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float MaxSearchDistance = 10.0f;

	void CorrectAttackAngle();
	
	AActor* SelectNearestEnemy();

	//MinDistance‚Ì”ÍˆÍ“à‚©‚Ç‚¤‚©‚ð”»’è‚·‚é
	inline bool IsInSearchRange(float distance)	{	return distance <= MaxSearchDistance;	}
};
