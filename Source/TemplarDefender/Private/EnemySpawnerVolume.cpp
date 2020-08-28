// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnerVolume.h"

// Sets default values
AEnemySpawnerVolume::AEnemySpawnerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnerVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

