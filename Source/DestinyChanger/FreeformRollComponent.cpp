//制作日：2023/07/10　制作者：トウ　更新内容：Roll処理コンポーネントの追加


#include "FreeformRollComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFreeformRollComponent::UFreeformRollComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UFreeformRollComponent::BeginPlay()
{
	Super::BeginPlay();
}

/// \brief Roll処理を実行する
void UFreeformRollComponent::RollProcess()
{
	if (bIsRolling) return;

	//Character Get
	ACharacter* Character = CastChecked<ACharacter>(GetOwner());

	//Rollモンタージュを再生
	if (RollMontage)	{
		bIsRolling = true;
		float _animeTime = Character->PlayAnimMontage(RollMontage);

		//SetTimer
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();

		_animeTime += RollCD;
		FTimerHandle TimerHandle;
		TimerManager.SetTimer(TimerHandle,this, &UFreeformRollComponent::ResetRollValue, _animeTime, false);
	}
}

void UFreeformRollComponent::ResetRollValue()
{
	bIsRolling = false;
}
