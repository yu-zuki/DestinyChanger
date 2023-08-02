//�X�V���F2023/07/17�@�X�V�ҁF�g�E�@�X�V���e�FUI�͂����ƃv���C���[�Ɍ��������̒ǉ�

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
//		�@�\

	//�������v���C���[�̕����Ɍ�����
	void LookAtPlayer();

	//Flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
		bool bIsLookAtPlayer = false;


	//HPUI���\��
	void HideHPUI();

	//ShowUI��Timer
	FTimerHandle ShowUITimerHandle;


public:
	//Set HP
	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetHPInfo(float HP, float MaxHP);
	//HPUI��\��
	void ShowHPUI(float _time);
};
