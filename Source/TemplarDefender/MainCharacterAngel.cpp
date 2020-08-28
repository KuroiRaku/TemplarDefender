// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAngel.h"
#include "Components/CapsuleComponent.h"

AMainCharacterAngel::AMainCharacterAngel()
	:Super()
{
	GetCapsuleComponent()->InitCapsuleSize(32.f, 96.0f);

	Health = 150;
	Speed = 1.5;
	Damage = 40;
}
