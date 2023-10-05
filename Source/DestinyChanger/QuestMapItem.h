//������F2023/08/26�@����ҁF�g�E�@�X�V���e�F�}�b�v��̃A�C�e���̃N���X

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

	//��b���I�������A�^�[�Q�b�g��Actor���X�|�[������
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void SpawnTargetActor();
};
