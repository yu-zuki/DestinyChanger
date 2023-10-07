//������F2023/09/28�@����ҁF�g�E�@�X�V���e�F�v���C���[���E����A�C�e���N���X
//������F2023/10/07�@����ҁF�g�E�@�X�V���e�F�N�G�X�g�A�C�e���Ƃ��Ă̋@�\��ǉ�

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
