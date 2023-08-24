// Copyright Epic Games, Inc. All Rights Reserved.

#include "DestinyChangerGameMode.h"
#include "DestinyChangerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "QuestDatabase.h"

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
	if (QuestDatabaseClass)	{
		QuestDatabaseInstance = GetWorld()->SpawnActor<AQuestDatabase>(QuestDatabaseClass);
	}

	//Print QuestDatabaseInstance Data
	UE_LOG(LogTemp, Warning, TEXT("Quest Database Initialized."));

	TArray<FQuestStruct> QuestDataArray = QuestDatabaseInstance->AllQuests;
	for (const FQuestStruct& QuestData : QuestDataArray)	{
		UE_LOG(LogTemp, Warning, TEXT("QuestID: %s, Description: %s"), *QuestData.QuestDetail.ID.ToString(), *QuestData.QuestDetail.Description.ToString());
	}
	

}

void ADestinyChangerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AttackEnd.Clear();	//Clear 
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

void ADestinyChangerGameMode::AddExp(float _Exp)
{
	//Playerを取得
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->AddExp(_Exp);
	}
}

AQuestDatabase* ADestinyChangerGameMode::GetQuestDatabase()
{
	if (QuestDatabaseInstance)	{
		return QuestDatabaseInstance;
	}

	return nullptr;
}
