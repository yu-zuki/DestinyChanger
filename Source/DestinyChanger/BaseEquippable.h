// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquippable.generated.h"

UCLASS()
class DESTINYCHANGER_API ABaseEquippable : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseEquippable();

private:
	bool bIsEquipped;		//装備中？

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equippable")
		class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equippable")
		class USkeletalMeshComponent* ItemSkeletalMesh;



	UFUNCTION()
		UPrimitiveComponent* GetItemMesh() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "initialize")
		FName AttachSocketName;	//装備時のアタッチ先
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void OnEquipped();

	UFUNCTION(BlueprintCallable)
		virtual void OnUnequipped();

	UFUNCTION(BlueprintCallable)
		void AttachActor(FName& _s_name);

	//-------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
		void SetIsEquipped(bool _bIsEquipped) { bIsEquipped = _bIsEquipped; }

	UFUNCTION(BlueprintCallable)
		bool GetIsEquipped() const { return bIsEquipped; }

	UFUNCTION(BlueprintCallable)
		void SetAttachSocketName(const FName& NewSocketName) { AttachSocketName = NewSocketName; }

	UFUNCTION(BlueprintCallable)
		FName GetAttachSocketName() const { return AttachSocketName; }

	//-------------------------------------------------------------------------

};
