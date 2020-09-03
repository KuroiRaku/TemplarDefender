// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
//#include "PaperSpriteComponent.h"
#include "DamageHitBox.h"
#include "MainCharacter.generated.h"




/**
 *
 */
UCLASS()
class TEMPLARDEFENDER_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//default is idle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* Angel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* Knight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* Demon;

	/**if we need to do it in C++, this is how we do it :p */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* AngelRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* KnightRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* DemonRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* AngelAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* KnightAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* DemonAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* AngelDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* KnightDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* DemonDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* KnightMeleeCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AngelMeleeCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* DemonMeleeCollisionBox;
	//TSubclassOf lets you restrict the types that can be assigned to a class property at runtime or compile time.
	//For instance, suppose you have a pickup class in your gameand you want to create a blueprintable pickup spawner for it.If you were to define your pickup spawner this way :
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ADamageHitBox> DamageHitBoxes;

	class ADamageHitBox* HitBox;
	/*UPROPERTY()
		class UPaperFlipbook* Temporary;*/

public:
	AMainCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnDeathEvent"))
		void SetAnimatorOnDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnAttackEvent"))
		void OnAttack();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "UpdateAnimatorEvent"))
	void UpdateAnimator();

	//UFUNCTION(BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnHurt"))
	//void OnHurt();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZZZ", meta = (DisplayName = "CharacterID"))
	int CharacterID;

	
	bool IsRunning = false;

	

	void OnDeath();

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "SetCharacterStats"))
	void SetCharacterStats();

	void SpawnHitBox(float Damage, EHitBoxType HitBoxType);


public:

	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "RunEvent"))
	void Run();

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "StopRunning"))
	void StopRunning();

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "AttackEvent"))
	void Attack();
	void StopAttacking();

	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();




protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	//TArray<ADamageHitBox*> HitboxesArray;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
