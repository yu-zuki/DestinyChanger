// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyTargeting.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChangerCharacter.h"

void UEnemyTargeting::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyTargeting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Enemy == nullptr || PlayerArrow == nullptr) {
		RemoveFromParent();
		return;
	}

	FRotator Rotator = GetLookAtRotationYaw();
	TargetingImage->SetRenderTransformAngle(Rotator.Yaw);
}

void UEnemyTargeting::Init(AActor* _Enemy, UArrowComponent* _PlayerArrow)
{
	Enemy = _Enemy;
	PlayerArrow = _PlayerArrow;
}

FRotator UEnemyTargeting::GetLookAtRotationYaw()
{
	if (Enemy == nullptr || PlayerArrow == nullptr) {
		RemoveFromParent();
		return FRotator();
	}

	FVector Start = Enemy->GetRootComponent()->GetComponentLocation();									//�G�̈ʒu
	FVector End = PlayerArrow->GetComponentLocation();		//�v���C���[�̈ʒu

	FVector Direction = End - Start;		//�v���C���[�̈ʒu����G�̈ʒu������
	Direction *= -1;						//���]

	Direction.Normalize(0.0001);
	float EnemyYaw = Direction.Rotation().Yaw;			//

	//-------------------------------Player-----------------------------------------
	auto tmp = PlayerArrow->GetForwardVector();
	tmp.Normalize(0.0001);
	float PlayerYaw = tmp.Rotation().Yaw;

	return FRotator(0, EnemyYaw - PlayerYaw, 0); //�G�̌����ƃv���C���[�̕����̍�����Ԃ�
}
