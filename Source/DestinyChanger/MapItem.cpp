//制作日：2023/08/28　制作者：トウ　更新内容：マップ上のアイテムクラス


#include "MapItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DialogueManager.h"

// Sets default values
AMapItem::AMapItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Components
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	//Create DialogueManager
	DialogueManager = CreateDefaultSubobject<UDialogueManager>(TEXT("DialogueManager"));

	//Set RootComponent
	RootComponent = MeshComponent;
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMapItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapItem::Interact(AActor* Caller)
{
	if (DialogueManager == nullptr) return;

	//Start Dialogue
	DialogueManager->EnterDialogue(Caller);
}

