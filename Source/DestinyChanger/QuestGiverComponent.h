//制作日：2023/08/25　制作者：トウ　更新内容：プレイヤーにクエストを与えるコンポーネントを作成

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestGiverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//////////////////////////////////////////////////////////////////////////
// GameMode
protected:
	class ADestinyChangerGameMode* GetGameMode();

	class ADestinyChangerGameMode* GameMode;

//////////////////////////////////////////////////////////////////////////
// Quest
public:
	//与えるのQuestID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName QuestID;

	//Questを与えた後、Actorを消すかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsDestroyAcotr;

	//入口
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayer();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayerWithID(FName _QuestID);

};
