// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Math/Rotator.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"

AEnemyCharacter::AEnemyCharacter()
	:Super()
{

	Speed = 1.0f;
	Health = 200;
	Damage = 20;
	EnemyType = 1;

	IsDead = false;
	IsAttacking = false;
	
	Enemy = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Knight"));
	//Enemy->SetFlipbook(EnemyRunning);
	Enemy->SetWorldScale3D(FVector(4, 4, 4));
	Enemy->SetRelativeScale3D(FVector(4, 4, 4));
	Enemy->SetRelativeRotation(FRotator(0, 90, 0));
	//Knight->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, -90));
	Enemy->SetupAttachment(RootComponent);
	Enemy->SetVisibility(true);

}

void AEnemyCharacter::Attack()
{
	
	IsAttacking = true;
	FTimerHandle UnusedHandle;


	
	SpawnHitBox(20, EHitBoxType::HB_DEMON);
	
	
	//OnAttack maybe can call in collision boxes etc
	
	Enemy->SetFlipbook(EnemyAttack);

	//First perimiter is using the timer, second 
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AEnemyCharacter::DestroyHitBox, 0.5f, false);
	Enemy->SetFlipbook(EnemyRunning);
	IsAttacking = false;

	
}



void AEnemyCharacter::SpawnHitBox(float Damage, EHitBoxType HitBoxType)
{
	FActorSpawnParameters SpawnParameters;
	// reference from the internet 
	// AProjectileArrow* spawnedArrow = (AProjectileArrow*) GetWorld()->SpawnActor(AProjectileArrow::StaticClass(), NAME_None, &yourLocation);
	FVector Result = GetActorLocation();
	if (GetActorRotation().Yaw == -180.f) {

		Result.Y -= 100;

	}
	else {

		Result.Y += 100;

	}
	DamageBox = GetWorld()->SpawnActor<ADamageHitBox>(Result, GetActorRotation(), SpawnParameters);
	DamageBox->Initialize(Damage, Result, HitBoxType);
	DamageBox->VisualizeHitbox();
	//HitboxesArray.Add(HitBox);

}

void AEnemyCharacter::OnDeath()
{
	FTimerHandle UnusedHandle;
	
	Enemy->SetFlipbook(EnemyDeath);
	
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AEnemyCharacter::DestroyActor, 1.f, false);
	
}

void AEnemyCharacter::DestroyHitBox()
{
	if (DamageBox->Destroy()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Destroyed Damageboxes! ");
	};
}

void AEnemyCharacter::DestroyActor()
{
	if (this->Destroy())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Enemy Dies! ");
	};
}

void AEnemyCharacter::Tick(float DeltaTime)
{
}
