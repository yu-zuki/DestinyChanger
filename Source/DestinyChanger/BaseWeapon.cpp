// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

void ABaseWeapon::AttachToHand()
{
	AttachActor(HandSocketName);
	bIsAttachToHand = false;
}

void ABaseWeapon::DetachFromHand()
{
	AttachActor( AttachSocketName );
	bIsAttachToHand = true;
}

void ABaseWeapon::OnEquipped()
{
	Super::OnEquipped();
}

void ABaseWeapon::OnUnequipped()
{
	Super::OnUnequipped();

}
