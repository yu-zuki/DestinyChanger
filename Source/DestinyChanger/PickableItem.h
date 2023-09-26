// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapItem.h"
#include "PickableItem.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API APickableItem : public AMapItem
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UItemGiverComponent* ItemGiverComponent;

public:
	APickableItem();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void PickableQuestItem();


	
};
