// Copyright Epic Games, Inc. All Rights Reserved.

#include "DestinyChangerGameMode.h"
#include "DestinyChangerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADestinyChangerGameMode::ADestinyChangerGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
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
