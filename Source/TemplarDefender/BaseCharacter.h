// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TEMPLARDEFENDER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(BlueprintReadOnly)
	float Health = 100;

	float Speed = 1.0f;
	int Damage = 10;
	bool IsDead = false;
	bool IsAttacking = false;

	virtual void CheckIfDead();
	virtual void AddHealth(float Delta);
	UFUNCTION(BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnHurt"))
	void OnHurt();
	virtual void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
