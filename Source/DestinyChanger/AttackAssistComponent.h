//������F2023/07/09�@����ҁF�g�E�@�������e�F�U���̎��A�F��ȕ֗��ȏ������s��
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�FCharacter�������Actor�Ɋp�x�i�����j���C�����鏈����ǉ�
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�F�v���C���[���G���U�������ۂ�HitStop������ǉ�
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�F�v���C���[���G���U�������ۂ�Effect������ǉ�
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

	//HitStop���s��
	void HitStop(float _HitStopSpeed = -1.f);

	//Effect��Spawn����
	void HitEffect(class UNiagaraSystem* _NiagaraSystem, FVector _HitLocation, FVector _HitDirection);

private:
	/// �ł��߂��G��I������B
	AActor* SelectNearestEnemy();

	//MinDistance�͈͓̔����ǂ����𔻒肷��
	inline bool IsInSearchRange(float distance)	{	return distance <= MaxSearchDistance;	}

	//HitStop����
	void HitStopProcess();


protected:
	//�@�\��Switch
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Assist")
		bool bUseCorrectAttackAngle = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Assist")
		bool bUseHitStop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Assist")
		bool bUseHitEffect = true;

	/// �G��\���x�[�X�ƂȂ�A�N�^�[�N���X�B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Assist")
		TSubclassOf<AActor> EnemyBaseClass;

	// �U���͈͓��ɂ���G�𔻒肷�邽�߂̋��� (�P��cm)�B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float MaxSearchDistance = 300.f;

	//HitStop�̑��x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float HitStopSpeed = 0.01f;

	//HitStop�̎���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackAssist" )
		float HitStopTime = 0.2f;

private:
	FTimerHandle TimerHandle_HitStop;
};