// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAssistComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

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

/// \brief �U���̊p�x���ł��߂��G�ɏC������B
void UAttackAssistComponent::CorrectAttackAngle()
{
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

void UAttackAssistComponent::HitStop(float _HitStopSpeed)
{
	//CharacterGet
	ACharacter* Character = Cast<ACharacter>(GetOwner());
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

/// \brief �ł��߂��G��I������
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

