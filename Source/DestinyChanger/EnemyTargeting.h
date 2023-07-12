// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyTargeting.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UEnemyTargeting : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//��z
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* TargetingCanvas;

	//�摜
	UPROPERTY(Meta = (BindWidget))
		class UImage* TargetingImage;

	void Init(AActor* _Enemy, class UArrowComponent* _PlayerArrow);
protected:
	//Enemy �̎Q��
	AActor* Enemy = nullptr;
	//Player�A���[
	class UArrowComponent* PlayerArrow = nullptr;

	//Init

	FRotator GetLookAtRotationYaw();
	
};
