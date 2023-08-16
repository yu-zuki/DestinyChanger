//制作日：2023/08/16　制作者：トウ　更新内容：クエストが必要な構造体を作成

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem.generated.h"

//クエストの会話
USTRUCT(BlueprintType)
struct FQuestDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト受注時の会話
	FText AcceptDialogue;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト提出時の会話
	FText SubmitDialogue;		
};

//クエストの種類
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	DefeatEnemy UMETA(DisplayName = "DefeatEnemy"),	//敵を倒す
	CollectItem UMETA(DisplayName = "CollectItem"),	//アイテムを集める
	TalkToNPC UMETA(DisplayName = "TalkToNPC")		//NPCと会話する
};


//クエストの詳細
USTRUCT(BlueprintType)
struct FQuestDetail
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストID
		FName ID;				

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//報酬経験値
		int32 RewardExp;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//報酬アイテム
		TMap<FName, int32> RewardItems;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの説明
		FText Description;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの種類
		EQuestType QuestType;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//必要な数
		int32 NeedNum;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //必要なターゲットID
		FName NeedTargetID;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//提出するターゲットID
		FName SubmitTargetID;	
};

//クエストの構造
USTRUCT(BlueprintType)
struct FQuestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト名
		FText QuestName;				

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト内容
		FText QuestContent;				

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの簡単な説明
		FText ShortDescription;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの詳細
		FQuestDetail QuestDetail;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの会話
		FQuestDialogue QuestDialogue;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストを受注するための条件
		FName ActiveCondition;			
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UQuestSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//GetPlayer
	class ADestinyChangerCharacter* GetPlayer();
	

protected:
	//激活的任务
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> ActiveQuests;
	//完成的任务
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> CompletedQuests;
	//执行的任务
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> ExecutingQuests;
	//任务道具
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, int32> QuestItems;
	//讨伐记录
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, int32> DefeatRecords;

////////////////////////////////////////////////////////////////////////////////////

	//添加激活的任务
	UFUNCTION(BlueprintCallable)
		void AddActiveQuest(FName QuestID);

	//添加完成的任务
	UFUNCTION(BlueprintCallable)
		void AddCompletedQuest(FName QuestID);

	//添加执行的任务
	UFUNCTION(BlueprintCallable)
		void AddExecutingQuest(FName QuestID);

	//添加任务道具
	UFUNCTION(BlueprintCallable)
		void AddQuestItem(FName ItemID, int32 Num);

	//添加讨伐记录
	UFUNCTION(BlueprintCallable)
		void AddDefeatRecord(FName EnemyID, int32 Num);
};
