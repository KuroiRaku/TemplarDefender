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
#include "VainCrystal.h"
#include "AIController.h"
#include "MainCharacter.h"
//AI
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyCharacter::AEnemyCharacter()
{

	Speed = 1.0f;
	Health = 200;
	Damage = 20;
	EnemyType = 1;

	IsDead = false;
	IsAttacking = false;

	FObjectInitializer& ObjectInitializer = FObjectInitializer::Get();
	this->AIControllerClass = AAIController::StaticClass();
	AAIController* AIController = Cast<AAIController>(this->GetController());
	
	Enemy = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Knight"));
	//Enemy->SetFlipbook(EnemyRunning);
	Enemy->SetWorldScale3D(FVector(4, 4, 4));
	Enemy->SetRelativeScale3D(FVector(4, 4, 4));
	Enemy->SetRelativeRotation(FRotator(0, 90, 0));
	//Knight->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, -90));
	Enemy->SetupAttachment(RootComponent);
	Enemy->SetVisibility(true);

	//AI
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnPawnSeen);
	

	//this method is to find allactors in the world to find the VainCrystal, but it is unoptimized...
	//last resort... lets use waypoint
	/*TArray<AActor*> VainCrystals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVainCrystal::StaticClass(), VainCrystals);
	AVainCrystal* VainCrystal = Cast<AVainCrystal> (VainCrystals.GetData());
	EPathFollowingRequestResult::Type MoveToActor
	(
		AActor * Goal,
		float AcceptanceRadius,
		bool bStopOnOverlap,
		bool bUsePathfinding,
		bool bCanStrafe,
		TSubclassOf < UNavigationQueryFilter > FilterClass,
		bool bAllowPartialPath
	);*/

	/*for (AWaypoint* A : WayPoints)
	{
		AIController->MoveToActor(A, 5.0f);
	}*/

	
	


}

void AEnemyCharacter::OnPawnSeen(APawn* SeenPawn)
{
	AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player==Cast<AMainCharacter>(SeenPawn))
	{
		FVector PlayerLocation = Player->GetActorLocation();
		MoveToLocation(PlayerLocation);
	};
	
	
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

		Result.Y -= 500.f;

	}
	else {

		Result.Y += 300.f;

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

void AEnemyCharacter::MoveToLocation(FVector Location)
{

	if (Location.Y > this->GetActorLocation().Y) {
		//set flipbook to left

		//when it is above the enemy
		if (Location.X > GetActorLocation().X)
		{
			AddMovementInput(FVector(1.0f, 1.0f, 0.0f), 1.0f);
		}
		else {
			AddMovementInput(FVector(-1.0f, 1.0f, 0.0f), 1.0f);
		}
		SetActorRotation(FRotator(0.f, -180.f, 0.f));

	}
	else {
		//going to right

		//when it is above the enemy
		if (Location.X > GetActorLocation().X)
		{
			AddMovementInput(FVector(1.0f, -1.0f, 0.0f), 1.0f);
		}
		else {
			AddMovementInput(FVector(-1.0f, -1.0f, 0.0f), 1.0f);
		}
		SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SeenPlayer) {

		if (WayPoints.Num()<=0) {
			for (AWaypoint* WayPoint : WayPoints)
			{
				FVector Location = WayPoint->GetActorLocation();
				//if the waypoint is at the left side of Enemy 

				MoveToLocation(Location);
			}
		}
		else {
			AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			MoveToLocation(Player->GetActorLocation());
		}
	}

}
