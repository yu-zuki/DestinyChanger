//更新日：2023/07/17　更新者：トウ　更新内容：ベースの敵キャラクターのUIClassの追加
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

	//HPバー
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

	//GetHP％
	inline float GetHPPercent() {
		return fHP / fMaxHP;
	}



	
};
