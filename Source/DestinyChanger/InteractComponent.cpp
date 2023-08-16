// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	//Create the components
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBoxComponent"));

	//Box Add Dynamic Delegate
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnOverlapBegin);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnOverlapEnd);
}

void UInteractComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//Attach the components to the owner
	if (GetOwner())	{
		BoxCollisionComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractObjectUIClass, "InteractObjectUI");
	//Add the widget to the viewport
	if (InteractWidget)	{
		InteractWidget->AddToViewport();
		InteractWidget->SetVisibility( ESlateVisibility::Hidden);
	}else	{
		UE_LOG(LogTemp, Warning, TEXT("InteractWidget is null"));
	}
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetInteractObject(OtherActor);
	SetUIActive(true);
}

void UInteractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetInteractObject(nullptr);
	SetUIActive(false);
}

void UInteractComponent::SetUIActive(bool bActive)
{
	if (InteractWidget)	{
		bActive ? InteractWidget->SetVisibility(ESlateVisibility::Visible) : InteractWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractComponent::SetInteractObject(AActor* Object)
{
	if(InteractObject != Object)	{
		InteractObject = Object;
	}
}

AActor* UInteractComponent::GetInteractObject()
{
	return InteractObject;
}

