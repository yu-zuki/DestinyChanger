// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackAssistComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UAttackAssistComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttackAssistComponent();

	/// �R���|�[�l���g�J�n���̓���B
	virtual void BeginPlay() override;

	/// �t���[�����̓���B
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// �U���̊p�x���C������B
	void CorrectAttackAngle();

	/// �ł��߂��G��I������B
	AActor* SelectNearestEnemy();

protected:

	/// �G��\���x�[�X�ƂȂ�A�N�^�[�N���X�B
	UPROPERTY(EditAnywhere, Category = "Attack Assist")
		TSubclassOf<AActor> EnemyBaseClass;

	// �U���͈͓��ɂ���G�𔻒肷�邽�߂̋��� (�P��cm)�B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float MaxSearchDistance = 300.f;

private:

	//MinDistance�͈͓̔����ǂ����𔻒肷��
	inline bool IsInSearchRange(float distance)	{	return distance <= MaxSearchDistance;	}
};
