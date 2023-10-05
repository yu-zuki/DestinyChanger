//������F2023/09/28�@����ҁF�g�E�@�X�V���e�F�v���C���[�ɃA�C�e����^����R���|�[�l���g

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemGiverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UItemGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//�^�����ItemID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TMap<FName, int32> ItemID;

	//����
	UFUNCTION(BlueprintCallable, Category = "Quest")
		void GiveItemToPlayer();
		
};
