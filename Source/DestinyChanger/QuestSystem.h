//制作日：2023/08/16　制作者：トウ　更新内容：クエストが必要な構造体を作成

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem.generated.h"

DECLARE_DELEGATE_OneParam(NotifyExecutingQuest, FName);
DECLARE_DELEGATE_OneParam(NotifyExecutingQuestComplete, FName);

//DECLARE_MULTICAST_DELEGATE(NotifyExecutingQuest);

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

//////////////////////////////////////////////////////////////////////////
// GameMode
protected:
	class ADestinyChangerGameMode* GetGameMode();

	class ADestinyChangerGameMode* GameMode;

protected:
	//アクティブなクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> ActiveQuests;
	//クリアしたクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> CompletedQuests;
	//実行中のクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> ExecutingQuests;
	//クエストアイテム
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FName, int32> QuestItems;
	//敵を倒した記録
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FName, int32> DefeatRecords;

////////////////////////////////////////////////////////////////////////////////////
public:
	//　受注可能なクエストを追加する
	UFUNCTION(BlueprintCallable)
		void AddActiveQuest(FName QuestID);

	//　クエストをクリアする
	UFUNCTION(BlueprintCallable)
		void AddCompletedQuest(FName QuestID);

	//　実行中のクエストを追加する
	UFUNCTION(BlueprintCallable)
		void AddExecutingQuest(FName QuestID);

	//　クエストアイテムを追加する
	UFUNCTION(BlueprintCallable)
		void AddQuestItem(FName ItemID, int32 Num);

	//　敵を倒した記録を追加する
	UFUNCTION(BlueprintCallable)
		void AddDefeatRecord(FName EnemyID, int32 Num);

////////////////////////////////////////////////////////////////////////////////////
//UI

public:
	//GetActiveQuests
	UFUNCTION(BlueprintCallable)
		TArray<FQuestStruct> GetActiveQuests();

	//GetCompletedQuests
	UFUNCTION(BlueprintCallable)
		TArray<FQuestStruct> GetCompletedQuests();

	//GetExecutingQuests
	UFUNCTION(BlueprintCallable)
		TArray<FQuestStruct> GetExecutingQuests();

	//GetQuestItems
	UFUNCTION(BlueprintCallable)
		int32 GetQuestItems(FName ItemID);

	//GetDefeatRecords
	UFUNCTION(BlueprintCallable)
		int32 GetDefeatRecords(FName ItemID);

	//実行中のクエストを追加したことをUIに通知
	NotifyExecutingQuest UINotifyExecutingQuest;

	template <typename ObjectType, typename MethodType>
	void BindUINotifyExecutingQuest(ObjectType* Object, MethodType Method)
	{
		UINotifyExecutingQuest.BindUObject(Object, Method);
	}

	//実行中のクエストを完了したことをUIに通知
	NotifyExecutingQuestComplete UINotifyExecutingQuestComplete;

	template <typename ObjectType, typename MethodType>
	void BindUINotifyExecutingQuestComplete(ObjectType* Object, MethodType Method)
	{
		UINotifyExecutingQuestComplete.BindUObject(Object, Method);
	}
};
