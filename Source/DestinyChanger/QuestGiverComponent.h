//������F2023/08/25�@����ҁF�g�E�@�X�V���e�F�v���C���[�ɃN�G�X�g��^����R���|�[�l���g���쐬

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestGiverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//////////////////////////////////////////////////////////////////////////
// GameMode
protected:
	class ADestinyChangerGameMode* GetGameMode();

	class ADestinyChangerGameMode* GameMode;

//////////////////////////////////////////////////////////////////////////
// Quest
public:
	//�^�����QuestID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName QuestID;

	//Quest��^������AActor���������ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsDestroyAcotr;

	//����
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayer();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayerWithID(FName _QuestID);

};
