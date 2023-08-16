// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableAPI.h"
#include "MapItem.generated.h"

UCLASS()
class DESTINYCHANGER_API AMapItem : public AActor, public IInteractableAPI
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Components" )
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Caller) override;
};
