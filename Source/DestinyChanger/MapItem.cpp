// Fill out your copyright notice in the Description page of Project Settings.


#include "MapItem.h"

// Sets default values
AMapItem::AMapItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

