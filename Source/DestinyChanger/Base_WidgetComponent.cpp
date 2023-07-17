// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "CharacterBase_UMG.h"



void UBase_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();


	SetWidgetSpace(EWidgetSpace::World);
	if (WidgetClass != nullptr)	{
		SetWidgetClass(WidgetClass);
	}
	
}

void UBase_WidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookAtPlayer();
}

//Œü‚«‚ðƒvƒŒƒCƒ„[‚ÉŒü‚¯‚é
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
