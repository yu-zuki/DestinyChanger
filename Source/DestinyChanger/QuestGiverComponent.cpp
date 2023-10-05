//制作日：2023/08/25　制作者：トウ　更新内容：プレイヤーにクエストを与えるコンポーネントを作成

#include "QuestGiverComponent.h"
#include "DestinyChangerCharacter.h"
#include "DestinyChangerGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "QuestDatabase.h"
#include "QuestSystem.h"
#include "InteractComponent.h"


// Sets default values for this component's properties
UQuestGiverComponent::UQuestGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ADestinyChangerGameMode* UQuestGiverComponent::GetGameMode()
{
	if (GetWorld() == nullptr) return nullptr;

	if(GameMode == nullptr){
		GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
		return GameMode;
	}

	return GameMode->IsValidLowLevel() ? GameMode : GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
}

void UQuestGiverComponent::GiveQuestToPlayer()
{
	if (QuestID.IsNone()) {
		UE_LOG(LogTemp, Warning, TEXT("QuestID is None"));
		return;
	}

	//GetPlayer
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player == nullptr) return;

	//Find QuestSystem
	UQuestSystem* QuestSystem = Player->FindComponentByClass<UQuestSystem>();
	if (QuestSystem == nullptr) return;

	//Add Quest to QuestSystem
	QuestSystem->AddExecutingQuest(QuestID);



	UInteractComponent* InteractComponent = Player->FindComponentByClass<UInteractComponent>();
	if (InteractComponent == nullptr) return;

	InteractComponent->SetUIActive(false);
	InteractComponent->SetInteractObject(nullptr);

	//DestroyActor
	GetOwner()->Destroy();	
}

