//�X�V���F2023/07/17�@�X�V�ҁF�g�E�@�X�V���e�FUI�͂����ƃv���C���[�Ɍ��������̒ǉ�


#include "Base_WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "CharacterBase_UMG.h"



void UBase_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	//���[���h�ŕ\������
	SetWidgetSpace(EWidgetSpace::World);	
	if (WidgetClass != nullptr)	{
		SetWidgetClass(WidgetClass);
	}

	SetVisibility(false);
	
}

void UBase_WidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookAtPlayer();
}

//�������v���C���[�Ɍ�����
void UBase_WidgetComponent::LookAtPlayer()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		//Get camera location
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager == nullptr) return;

		UCameraComponent* CameraComponent = Cast<UCameraComponent>(CameraManager->GetViewTarget()->GetComponentByClass(UCameraComponent::StaticClass()));
		if (CameraComponent == nullptr) return;

		FVector CameraLocation = CameraComponent->GetComponentLocation();
		//Look at camera
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), CameraLocation);

		//ReSet rotation
		LookAtRotation.Pitch = 0.0f;
		LookAtRotation.Roll = 0.0f;

		//Apply rotation
		SetWorldRotation(LookAtRotation);
	}
}

void UBase_WidgetComponent::ShowHPUI(float _time)
{
	//Component ��Actor���擾
	AActor* Owner = GetOwner();

	//Widget��\��
	SetVisibility(true);

	Owner->GetWorldTimerManager().SetTimer(ShowUITimerHandle, this, &UBase_WidgetComponent::HideHPUI, _time, false);

}

void UBase_WidgetComponent::HideHPUI()
{
	//Component ��Actor���擾
	AActor* Owner = GetOwner();

	SetVisibility(false);

	Owner->GetWorldTimerManager().ClearTimer(ShowUITimerHandle);
}

void UBase_WidgetComponent::SetHPInfo(float HP, float MaxHP)
{
	if (WidgetClass != nullptr) {
		//Get Character Widget
		UCharacterBase_UMG* CharacterWidget = Cast<UCharacterBase_UMG>(GetWidget());
		if (CharacterWidget != nullptr) {
			//Set HP
			CharacterWidget->SetPlayerInfo(HP, MaxHP);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("CharacterWidget is nullptr"));
		}
	}
}
