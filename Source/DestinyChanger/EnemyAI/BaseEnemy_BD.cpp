// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy_BD.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/EnumProperty.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"




UBaseEnemy_BD::UBaseEnemy_BD()
{
	EnemyStateKey.EntryName = "EnemyState";
	UBlackboardKeyType_Enum* EnemyStateEnum = NewObject<UBlackboardKeyType_Enum>();

	EnemyStateEnum->EnumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyState"), true);
	EnemyStateEnum->EnumName = "EEnemyState";
	EnemyStateKey.KeyType = EnemyStateEnum;
	Keys.Add(EnemyStateKey);
}
