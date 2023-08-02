//更新日：2023/07/17　更新者：トウ　更新内容：UIはずっとプレイヤーに向く処理の追加

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
//		機能

	//向きをプレイヤーの方向に向ける
	void LookAtPlayer();

	//Flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
		bool bIsLookAtPlayer = false;


	//HPUIを非表示
	void HideHPUI();

	//ShowUIのTimer
	FTimerHandle ShowUITimerHandle;


public:
	//Set HP
	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetHPInfo(float HP, float MaxHP);
	//HPUIを表示
	void ShowHPUI(float _time);
};
