//制作日：2023/07/18　制作者：トウ　処理内容：敵の状態を管理するブラックボードデータ

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "BaseEnemy_BD.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Patrol UMETA(DisplayName = "Patrol"),
	Chase UMETA(DisplayName = "Chase"),
	Attack UMETA(DisplayName = "Attack"),
	Return UMETA(DisplayName = "Return")
};

struct FBlackboardEntry;
/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API UBaseEnemy_BD : public UBlackboardData
{
	GENERATED_BODY()

public:
	UBaseEnemy_BD();
	
	FBlackboardEntry EnemyStateKey;
};
