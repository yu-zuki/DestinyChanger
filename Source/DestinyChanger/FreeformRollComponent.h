//������F2023/07/10�@����ҁF�g�E�@�X�V���e�FRoll�����R���|�[�l���g�̒ǉ�

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

	//Roll��CD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FreeformRoll")
		float RollCD = 0.5f;

private:
	//RollProcess���K�v�ȕϐ��@
	FVector2D MovementVector;	//�ړ���
	FVector ForwardDriction;	//�O����
	FVector RightDriction;		//�E����

	bool bIsRolling = false;			//Roll�����ǂ���

public:
	//RollProcess
	void RollProcess();

	//ResetRollValue
	void ResetRollValue();

};
