// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
//#include "PaperSpriteComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* Angel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* Knight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* Demon;



public:
	AMainCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable ,Category = "ZZZ", meta = (DisplayName = "OnAttackEvent"))
	void OnAttack();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "UpdateAnimatorEvent"))
	void UpdateAnimator();

	//UFUNCTION(BlueprintCallable, Category = "ZZZ", meta = (DisplayName = "OnHurt"))
	//void OnHurt();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZZZ", meta = (DisplayName = "CharacterID"))
	int CharacterID;

	bool IsDead = false;
	bool IsRunning = false;

	void OnDeath();

	void SetCharacterStats();


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

	void Run();

	void StopRunning();

	void Attack();


	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();




protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
