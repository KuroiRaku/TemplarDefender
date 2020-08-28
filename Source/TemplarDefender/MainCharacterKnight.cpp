// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterKnight.h"
#include "Components/CapsuleComponent.h"

AMainCharacterKnight::AMainCharacterKnight()
	:Super()
{
	
	Health = 150;
	Speed = 1.5;
	Damage = 80;
	IsDead = false;
}

void AMainCharacterKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacterKnight::attack()
{
	
}
