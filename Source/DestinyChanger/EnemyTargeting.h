//更新日：2023/07/13　更新者：トウ　更新内容：敵の方向を示すUIの追加

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

	//画布
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* TargetingCanvas;

	//画像
	UPROPERTY(Meta = (BindWidget))
		class UImage* TargetingImage;

	void Init(AActor* _Enemy, class UArrowComponent* _PlayerArrow);
protected:
	//EnemyPtr の参照
	AActor* Enemy = nullptr;
	//Playerアロー
	class UArrowComponent* PlayerArrow = nullptr;

	//Init

	FRotator GetLookAtRotationYaw();
	
};
