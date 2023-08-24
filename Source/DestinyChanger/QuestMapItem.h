// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapItem.h"
#include "QuestMapItem.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API AQuestMapItem : public AMapItem
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UQuestGiverComponent* QuestGiverComponent;

public:
	AQuestMapItem();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayer();
};
