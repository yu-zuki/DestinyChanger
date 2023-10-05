//制作日：2023/07/08　制作者：トウ　処理内容：ゲームのルール

#include "DestinyChangerGameMode.h"
#include "DestinyChangerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "QuestDatabase.h"
#include "ItemDataBase.h"

ADestinyChangerGameMode::ADestinyChangerGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void ADestinyChangerGameMode::BeginPlay()
{
	//データベースの生成　（効率が悪くなります、今後Singletonで設計する）
	if (QuestDatabaseClass)	{
		QuestDatabaseInstance = GetWorld()->SpawnActor<AQuestDatabase>(QuestDatabaseClass);
	}

	if (ItemDatabaseClass) {
		ItemDatabaseInstance = GetWorld()->SpawnActor<AItemDataBase>(ItemDatabaseClass);
	}

	//Print QuestDatabaseInstance Data
	UE_LOG(LogTemp, Warning, TEXT("Quest Database Initialized."));

	TArray<FQuestStruct> QuestDataArray = QuestDatabaseInstance->AllQuests;
	for (const FQuestStruct& QuestData : QuestDataArray)	{
		UE_LOG(LogTemp, Warning, TEXT("QuestID: %s, Description: %s"), *QuestData.QuestDetail.ID.ToString(), *QuestData.QuestDetail.Description.ToString());
	}

	TArray<FItemStruct> ItemDataArray = ItemDatabaseInstance->AllItems;
	for (const FItemStruct& ItemData : ItemDataArray) {
		UE_LOG(LogTemp, Warning, TEXT("ItemID: %s, Description: %s"), *ItemData.ID.ToString(), *ItemData.Description.ToString());
	}
	

}

/**
 * @brief   EndPlay関数は、ゲームモードの終了時に呼び出される関数です。
 *
 * @details AttackEndのデリゲートをクリアします。
 *
 * @return  なし
 */
void ADestinyChangerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
	//　（　プレイヤーが一回の攻撃は敵に与えるダメージが一回のみになるようにするため、
	//		攻撃が終わったら敵のダメージ受けフラグをリセットする）
	AttackEnd.Clear();	//	AttackEndのデリゲートをクリアします。
}

/**
 * @brief   AttackEndEventCall関数は、全ての敵キャラクターが攻撃を受けられるようにする関数です。
 *
 * @details この関数を呼び出すことで、全ての敵キャラクターが攻撃を受けられるようになっていきます。
 *
 * @return  なし
 */
void ADestinyChangerGameMode::AttackEndEventCall()
{
	AttackEnd.Broadcast();	//Call 全ての敵が攻撃を受けられるようにする
}

/**
 * @brief   AddExp関数は、経験値を増加させるための関数です。
 *
 * @details プレイヤーを取得し、経験値を増加させます。
 *
 * @param[in] _Exp 増加させる経験値
 *
 * @return  なし
 */
void ADestinyChangerGameMode::AddExp(float _Exp)
{
	//Playerを取得
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->AddExp(_Exp);
	}
}

/**
 * @brief   GetQuestDatabase関数は、QuestDatabaseInstanceを返す関数です。
 *
 * @details QuestDatabaseInstanceがある場合、そのインスタンスを返します。
 *
 * @return  QuestDatabaseInstanceがある場合、そのインスタンスを返します。それ以外の場合は、nullptrを返します。
 */
AQuestDatabase* ADestinyChangerGameMode::GetQuestDatabase()
{
	if (QuestDatabaseInstance)	{
		return QuestDatabaseInstance;
	}

	return nullptr;
}

/**
 * @brief   GetItemDatabase関数は、ItemDatabaseInstanceを返す関数です。
 *
 * @details ItemDatabaseInstanceがある場合、そのインスタンスを返します。
 *
 * @return  ItemDatabaseInstanceがある場合、そのインスタンスを返します。それ以外の場合は、nullptrを返します。
 */
AItemDataBase* ADestinyChangerGameMode::GetItemDatabase()
{
	if (ItemDatabaseInstance) {
		return ItemDatabaseInstance;
	}

	return nullptr;
}
