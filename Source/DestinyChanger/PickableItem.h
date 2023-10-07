//制作日：2023/09/28　制作者：トウ　更新内容：プレイヤーが拾えるアイテムクラス
//制作日：2023/10/07　制作者：トウ　更新内容：クエストアイテムとしての機能を追加

#pragma once

#include "CoreMinimal.h"
#include "MapItem.h"
#include "QuestActorInterface.h"

#include "PickableItem.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API APickableItem : public AMapItem, public IQuestActorInterface
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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetActorDeepHidden(bool _isHidden = true);

	virtual void SetActorDeepHidden_Implementation(bool _isHidden) override;

	
};
