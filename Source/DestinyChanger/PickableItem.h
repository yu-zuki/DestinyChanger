//制作日：2023/09/28　制作者：トウ　更新内容：プレイヤーが拾えるアイテムクラス

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

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetActorDeepHidden(bool _isHidden);

	
};
