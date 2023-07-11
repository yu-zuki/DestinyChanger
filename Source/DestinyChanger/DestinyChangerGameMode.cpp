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
 * @brief   AttackEndEventCall�֐��́A�S�Ă̓G�L�����N�^�[���U�����󂯂���悤�ɂ���֐��ł��B
 *
 * @details ���̊֐����Ăяo�����ƂŁA�S�Ă̓G�L�����N�^�[���U�����󂯂���悤�ɂȂ��Ă����܂��B
 *
 * @return  �Ȃ�
 */
void ADestinyChangerGameMode::AttackEndEventCall()
{
	AttackEnd.Broadcast();	//Call �S�Ă̓G���U�����󂯂���悤�ɂ���
}
