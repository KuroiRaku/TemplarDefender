// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageHitBox.generated.h"

UENUM()
enum class EHitBoxType
{
	HB_ANGEL,
	HB_KNIGHT,
	HB_DEMON,
	HB_ENEMY1,
	HB_ENEMY2
};

UCLASS()
class TEMPLARDEFENDER_API ADamageHitBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBox;

	//the colour of the boxes where it shows where it going to hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* HitColor;

	//the colour of the boxes where it actually damage the enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* DamageColor;

	//Default Colour, kinda useless for now
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitBoxes", meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* Color;

	/*UPROPERTY(VisibleAnywhere)
	class UMaterial* StoredMaterial;*/

	//UMaterialInstanceDynamic* DynamicMaterialInstance;


public:	
	// Sets default values for this actor's properties
	ADamageHitBox();

	void Initialize(float Damage, FVector Location, EHitBoxType HitBoxType);

	//draw the hitbox ro the screen
	void VisualizeHitbox();



	bool IfCollides();

	FVector HitBoxLocation;

	float Damage;

	EHitBoxType HitBoxType;
	
	//void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void BeginPlay() override;

};

