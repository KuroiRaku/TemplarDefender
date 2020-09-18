// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DamageHitBox.h"
#include "AIController.h"
#include "Waypoint.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLARDEFENDER_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	

public:
	AEnemyCharacter();

	UPROPERTY(BlueprintReadWrite)
	int EnemyType;

	UPROPERTY(BlueprintReadWrite)
	bool SeenPlayer;


	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ADamageHitBox> DamageHitBoxes;

	//this pointer will get a reference on runtime after being spawn in. 
	//The spawn actor function will assign pointer of the object that it spawned to this
	UPROPERTY(EditAnywhere)
	class ADamageHitBox* DamageBox;

	UPROPERTY(EditAnywhere)
	TArray<AWaypoint*> WayPoints;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	
	
	
	UFUNCTION(BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "Attack Event"))
	void Attack();

	void SpawnHitBox(float Damage, EHitBoxType HitBoxType);

	void OnDeath();


	//sadly i need these functions so we are compatible with setTimer functions... 
	void DestroyHitBox();

	void DestroyActor();

	void MoveToLocation(FVector Location);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//blueprint event 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnAttackEvent"))
	void OnAttack();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "UpdateAnimatorEvent"))
	void UpdateAnimator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* Enemy;

	//idle animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* EnemyRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* EnemyDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* EnemyAttack;
};
