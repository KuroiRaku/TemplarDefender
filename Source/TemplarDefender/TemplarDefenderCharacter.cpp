// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TemplarDefenderCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"


//////////////////////////////////////////////////////////////////////////
// ATemplarDefenderCharacter

ATemplarDefenderCharacter::ATemplarDefenderCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-85.0f, 0.0f, 0.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATemplarDefenderCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATemplarDefenderCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATemplarDefenderCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "MousePitch" handles devices that provide an absolute delta, such as a mouse.
	
	PlayerInputComponent->BindAxis("MousePitch", this, &ATemplarDefenderCharacter::PitchCamera);
	
	PlayerInputComponent->BindAxis("MouseYaw", this, &ATemplarDefenderCharacter::YawCamera);
	

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ATemplarDefenderCharacter::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ATemplarDefenderCharacter::ZoomOut);
	
}

void ATemplarDefenderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
	FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	CameraBoom->TargetArmLength = FMath::Lerp<float>(600.0f, 400.0f, ZoomFactor);


	FRotator NewYaw = GetActorRotation();
	NewYaw.Yaw += CameraInput.X;
	SetActorRotation(NewYaw);
//
//	FRotator NewPitch = CameraBoom->GetComponentRotation();
//	//we should discuss whether we should make player able to look at character closer :p
////	NewPitch.Pitch = FMath::Clamp<float>(NewPitch.Pitch + CameraInput.Y, -90.0f, -90.0f);
//	CameraBoom->SetWorldRotation(NewPitch);
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(TEXT("%.5d", GetActorRotation())));
}

void ATemplarDefenderCharacter::CalculateDead()
{
	if (Health <= 0)
		IsDead = true;
	else
		IsDead = false;
}

void ATemplarDefenderCharacter::CalculateHealth(float Delta)
{
	Health += Delta;
	CalculateDead();
}

void ATemplarDefenderCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATemplarDefenderCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATemplarDefenderCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ATemplarDefenderCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ATemplarDefenderCharacter::ZoomIn()
{
	bZoomingIn = true;
}

void ATemplarDefenderCharacter::ZoomOut()
{
	bZoomingIn = false;
}
