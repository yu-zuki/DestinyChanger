//制作日：2023/08/26　制作者：トウ　更新内容：マップ上のアイテムのクラス

#pragma once

#include "CoreMinimal.h"
#include "MapItem.h"
#include "QuestActorInterface.h"


#include "QuestMapItem.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API AQuestMapItem : public AMapItem ,public IQuestActorInterface
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

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void ActiveTargetActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetActorDeepHidden(bool _isHidden = true);

	virtual void SetActorDeepHidden_Implementation(bool _isHidden) override;

};
