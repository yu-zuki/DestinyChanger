//�X�V���F2023/07/17�@�X�V�ҁF�g�E�@�X�V���e�F�x�[�X�̓G�L�����N�^�[��UIClass�̒ǉ�
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterBase_UMG.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UCharacterBase_UMG : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* Canvas;

	//HP�o�[
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HealthBar;

protected:
	//-------------------------------
	//widgetValue
	float fHP = 0.f;
	float fMaxHP = 0.f;

	FName Name = FName("None");

public:

	void SetPlayerInfo(float HP, float MaxHP);

	//GetHP��
	inline float GetHPPercent() {
		return fHP / fMaxHP;
	}



	
};
