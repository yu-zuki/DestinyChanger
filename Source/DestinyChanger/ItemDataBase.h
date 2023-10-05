//������F2023/09/28�@����ҁF�g�E�@�X�V���e�F�A�C�e���̃f�[�^�x�[�X

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataBase.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	//�N�G�X�g�̃A�C�e��
	QuestItem UMETA(DisplayName = "QuestItem")
};

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;

	//�N�G�X�g�̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		EItemType ItemType;

	//�A�C�e���̖��O
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		FText ItemName;

	//�A�C�e���̐���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		FText Description;
};

UCLASS()
class DESTINYCHANGER_API AItemDataBase : public AActor
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FItemStruct> AllItems;

	UFUNCTION(BlueprintCallable, Category = "Quest")
		bool ItemExists(FName ID) const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
		FItemStruct GetItem(FName ID) const;
	

};
