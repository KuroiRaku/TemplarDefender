// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterDemon.h"

AMainCharacterDemon::AMainCharacterDemon()
	:Super()
{
	GetCapsuleComponent()->InitCapsuleSize(32.f, 96.0f);

	Health = 300;
	Speed = 0.9;
	Damage = 100;
}

