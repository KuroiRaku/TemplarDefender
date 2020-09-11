// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TEMPLARDEFENDER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* HitBox;



public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(BlueprintReadWrite)
	float Health = 100;
	UPROPERTY(BlueprintReadWrite)
	float Speed = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	int Damage = 10;
	UPROPERTY(BlueprintReadWrite)
	bool IsDead = false;
	UPROPERTY(BlueprintReadWrite)
	bool IsAttacking = false;



	virtual void CheckIfDead();
	virtual void AddHealth(float Delta);
	UFUNCTION(BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnHurt"))
	void OnHurt(float Delta);
	virtual void OnDeath();

	//UFUNCTION(BlueprintCallable, meta=(DisplayName ="BeginOverlap"))
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
