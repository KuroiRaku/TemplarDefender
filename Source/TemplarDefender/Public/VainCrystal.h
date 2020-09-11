// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VainCrystal.generated.h"

UCLASS()
class TEMPLARDEFENDER_API AVainCrystal : public AActor
{
	//best practice is to implement a health system using interface... But too lazy to create one ;_; 
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBox;


	
public:	
	// Sets default values for this actor's properties
	AVainCrystal();

	UPROPERTY(BlueprintReadWrite)
	float Health = 10000;

	UPROPERTY(BlueprintReadWrite)
	bool IsDestroyed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Crystal ;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void CheckIfDestroyed();
	virtual void AddHealth(float Delta);
	UFUNCTION(BlueprintCallable, Category = "VainCrystal", meta = (DisplayName = "OnHurt"))
	void OnHurt(float Delta);

	virtual void OnDeath();

};
