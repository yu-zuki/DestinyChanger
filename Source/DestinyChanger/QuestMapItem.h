//制作日：2023/08/26　制作者：トウ　更新内容：マップ上のアイテムのクラス

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

	//会話が終わったら、ターゲットのActorをスポーンする
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void SpawnTargetActor();
};
