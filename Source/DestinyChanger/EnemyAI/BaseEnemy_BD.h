//������F2023/07/18�@����ҁF�g�E�@�������e�F�G�̏�Ԃ��Ǘ�����u���b�N�{�[�h�f�[�^

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
