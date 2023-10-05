//制作日：2023/09/28　制作者：トウ　更新内容：アイテムのデータベース

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataBase.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	//クエストのアイテム
	QuestItem UMETA(DisplayName = "QuestItem")
};

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;

	//クエストの種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		EItemType ItemType;

	//アイテムの名前
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		FText ItemName;

	//アイテムの説明
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
