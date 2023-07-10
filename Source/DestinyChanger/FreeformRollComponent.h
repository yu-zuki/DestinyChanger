//制作日：2023/07/10　制作者：トウ　更新内容：Roll処理コンポーネントの追加

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FreeformRollComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UFreeformRollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFreeformRollComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	//AnimationMontage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeformRoll")
		class UAnimMontage* RollMontage;

	//RollのCD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeformRoll")
		float RollCD = 0.5f;

private:
	//RollProcessが必要な変数　
	FVector2D MovementVector;	//移動量
	FVector ForwardDriction;	//前方向
	FVector RightDriction;		//右方向

	bool bIsRolling = false;			//Roll中かどうか

public:
	//RollProcess
	void RollProcess();

	//ResetRollValue
	void ResetRollValue();

};
