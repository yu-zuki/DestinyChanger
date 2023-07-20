//制作日：2023/07/18　制作者：トウ　処理内容：敵のAIコントローラー

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
	//ビヘイビアツリー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BehaviorTree;

public:
	//Get
	//class UBehaviorTreeComponent* GetBehaviorTreeComponent() const;
	//class UBlackboardComponent* GetBlackboardComponent() const;
	
};
