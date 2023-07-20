//������F2023/07/18�@����ҁF�g�E�@�������e�F�G��AI�R���g���[���[

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemy_AIC.generated.h"

/**
 * 
 */
UCLASS()
class DESTINYCHANGER_API ABaseEnemy_AIC : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	//�r�w�C�r�A�c���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BehaviorTree;

public:
	//Get
	//class UBehaviorTreeComponent* GetBehaviorTreeComponent() const;
	//class UBlackboardComponent* GetBlackboardComponent() const;
	
};
