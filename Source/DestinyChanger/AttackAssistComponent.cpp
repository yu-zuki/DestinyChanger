//������F2023/07/09�@����ҁF�g�E�@�������e�F�U���̎��A�F��ȕ֗��ȏ������s��
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�FCharacter�������Actor�Ɋp�x�i�����j���C�����鏈����ǉ�
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�F�v���C���[���G���U�������ۂ�HitStop������ǉ�
//������F2023/07/09�@����ҁF�g�E�@�X�V���e�F�v���C���[���G���U�������ۂ�Effect������ǉ�

#include "AttackAssistComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UAttackAssistComponent::UAttackAssistComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAttackAssistComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UAttackAssistComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
* @brief �U���p�x���C������֐�
* 
* @details �ł��߂��G���擾���A�v���C���[�ƓG�̕������v�Z���ăv���C���[�̌�����ύX����
* 
* @return void
*/
void UAttackAssistComponent::CorrectAttackAngle()
{
	//�@�\�g�p���邩�ǂ����̃`�F�b�N
	if (!bUseCorrectAttackAngle) return;

	//�������e
	AActor* NearestEnemy = SelectNearestEnemy();	// �ł��߂��G���擾����

	if (NearestEnemy != nullptr) {
	
		// �v���C���[�ƓG�̕������擾����
		FVector direction = NearestEnemy->GetActorLocation() - GetOwner()->GetActorLocation();
		direction.Normalize();

		// �v���C���[�̌������擾����
		FRotator CurrentRotation = GetOwner()->GetActorRotation();

		// �v���C���[�̌�����ύX����
		FRotator NewRotation(CurrentRotation.Pitch, direction.Rotation().Yaw, CurrentRotation.Roll);
		GetOwner()->SetActorRotation(NewRotation);
	}
}

/**
 * @brief �q�b�g�X�g�b�v�𔭐�������
 * 
 * @details bUseHitStop��false�Ȃ珈�����s��Ȃ��B
 *			Character�I�u�W�F�N�g���L���X�g���AAnimation�̍Đ����x��_HitStopSpeed�ɂ���B
 *			HitStopTime��ɏ������I������B
 * 
 * @param _HitStopSpeed �q�b�g�X�g�b�v�̑��x
 * 
 * @return �Ȃ�
 */
void UAttackAssistComponent::HitStop(float _HitStopSpeed)
{
	//�@�\�g�p���邩�ǂ����̃`�F�b�N
	if (!bUseHitStop) return;

	//�������e
	ACharacter* Character = Cast<ACharacter>(GetOwner());		//CharacterGet
	if (Character == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: Character is nullptr"));
		return;
	}

	//HitStop���J�n
	Character->GetMesh()->GlobalAnimRateScale = _HitStopSpeed > 0.f ? _HitStopSpeed : HitStopSpeed;

	//HitStop���~
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(TimerHandle_HitStop, this, &UAttackAssistComponent::HitStopProcess, HitStopTime, false);
}

/**
 * @brief �U���G�t�F�N�g�̐���
 * 
 * @details Niagara�V�X�e���𐶐����āA�U���̈ʒu�ɃX�|�[������B
 * 
 * @param _NiagaraSystem ��������Niagara�V�X�e��
 * 
 * @param _HitLocation �U���̈ʒu
 * 
 * @param _HitDirection �U���̕���
 */
void UAttackAssistComponent::HitEffect(UNiagaraSystem* _NiagaraSystem, FVector _HitLocation, FVector _HitDirection)
{
	//�@�\�g�p���邩�ǂ����̃`�F�b�N
	if (!bUseHitEffect) return;

	//�������e
	if (_NiagaraSystem == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: NiagaraSystem is nullptr"));
		return;
	}

	FVector AntiHitDirection = _HitDirection * -1;
	FRotator HitRotation = FRotator(AntiHitDirection.Rotation().Pitch, 0.f, 0.f);

	FVector Scale = FVector(0.7f, 0.7f, 0.7f);
	//Spawn
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),_NiagaraSystem,_HitLocation,HitRotation,Scale);
}

///	@brief �ł��߂��G��T���֐�
/// 
///	@details �Q�[�����[���h���̑S�Ă̓G���擾���A�v���C���[�̈ʒu�Ƃ̋������Z�o���A�ł��߂��G��Ԃ��܂��B
/// 
///	@return �ł��߂��G�̃A�N�^�[	AActor * 
AActor* UAttackAssistComponent::SelectNearestEnemy()
{
	if (EnemyBaseClass == nullptr)	{

		// �G���[����
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: EnemyBaseClass is nullptr"));
		return nullptr;
	}

	// �S�Ă̓G���擾����
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyBaseClass, FoundEnemies);

	float MinDistance = MAX_FLT;
	AActor* NearestEnemy = nullptr;

	for ( auto enemy : FoundEnemies)
	{
		// �v���C���[�ƓG�̋������擾����
		float distance = FVector::Distance(GetOwner()->GetActorLocation(), enemy->GetActorLocation());

		if (IsInSearchRange(distance)){
			if (distance < MinDistance) {
				MinDistance = distance;
				NearestEnemy = enemy;
			}
		}
	}
	
	if (NearestEnemy != nullptr) {
		return NearestEnemy;
	}

	return nullptr;
}

/**
 * @brief �q�b�g�X�g�b�v�̏���
 *
 * @details Character�I�u�W�F�N�g���L���X�g���AAnimation�̍Đ����x��1.0f�ɂ���B
 *
 * @return �Ȃ�
 */
void UAttackAssistComponent::HitStopProcess()
{
	//CharacterGet
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttackAssitComponent: Character is nullptr"));
		return;
	}

	//HitStop���~
	Character->GetMesh()->GlobalAnimRateScale = 1.f;
}

