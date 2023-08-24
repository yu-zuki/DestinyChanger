//������F2023/08/25�@����ҁF�g�E�@�X�V���e�F�N�G�X�g�̃f�[�^�x�[�X�N���X���쐬

#pragma once


#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystem.h"
#include "QuestDatabase.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API AQuestDatabase : public AActor
{
	GENERATED_BODY()

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuestStruct> AllQuests;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool QuestExists(FName ID) const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	FQuestStruct GetQuest(FName ID) const;
	
};
