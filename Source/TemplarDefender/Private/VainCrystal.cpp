// Fill out your copyright notice in the Description page of Project Settings.


#include "VainCrystal.h"
#include "DamageHitBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
AVainCrystal::AVainCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	
	HitBox->SetHiddenInGame(false);
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	HitBox->SetWorldScale3D(FVector(0.5, 0.5, 0.5));

	Crystal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal"));
	Crystal->SetupAttachment(HitBox);
	Crystal->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void AVainCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVainCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVainCrystal::CheckIfDestroyed()
{
	if (Health <= 0) {
		Health = 0;
		IsDestroyed = true;
		OnDeath();
	}
	else
		IsDestroyed = false;
}

void AVainCrystal::AddHealth(float Delta)
{
	Health += Delta;
	CheckIfDestroyed();
}

void AVainCrystal::OnHurt(float Delta)
{
	AddHealth(-Delta);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Crystal got damaged: %f"), Health));
}

void AVainCrystal::OnDeath()
{
	this->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Crystal got destroyed")));
}

