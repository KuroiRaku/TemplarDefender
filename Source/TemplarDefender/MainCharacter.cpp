// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
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

AMainCharacter::AMainCharacter()

{


	//Super::ABaseCharacter();
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	


	//Character Switching Variables
	CharacterID = 1;//0 = Demon, 1 = Knight, 2 = Angel

	Speed = 1.0f;
	Health = 200;
	Damage = 50;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//Create the character Sprite
	Knight = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Knight"));
	Knight->SetWorldScale3D(FVector(4, 4, 4));
	Knight->SetRelativeScale3D(FVector(4, 4, 4));
	Knight->SetRelativeRotation(FRotator(0,90, 0));
	//Knight->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, -90));
	Knight->SetupAttachment(RootComponent);
	Knight->SetVisibility(true);


	Angel = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Angel"));
	Angel->SetupAttachment(RootComponent);
	Angel->SetWorldScale3D(FVector(4, 4, 4));
	Angel->SetRelativeScale3D(FVector(4, 4, 4));
	Angel->SetRelativeRotation(FRotator(0, 90, 0));
	Angel->SetVisibility(false);

	Demon= CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Demon"));
	Demon->SetupAttachment(RootComponent);
	Demon->SetWorldScale3D(FVector(4, 4, 4));
	Demon->SetRelativeScale3D(FVector(4, 4, 4));
	Demon->SetRelativeRotation(FRotator(0, 90, 0));
	Demon->SetVisibility(false);
	

	/*RootComponent->SetWorldScale3D(FVector(3, 3, 3));
	RootComponent->SetRelativeScale3D(FVector(3, 3, 3));*/

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-45.0f, 0.0f, 0.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMainCharacter::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);

	/*if (IsRunning)
	{


	}
	else {


	}*/
	//UpdateAnimator();
	//Switch Characters?
	if (IsDead)
	{
		OnDeath();
		UpdateAnimator();
	}



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
	CameraBoom->TargetArmLength = FMath::Lerp<float>(1100.0f, 900.0f, ZoomFactor);


	FRotator NewYaw = GetActorRotation();
	NewYaw.Yaw += CameraInput.X;

	//
	//SetActorRotation(NewYaw);
	// Trying to debug below O.O
	//	FRotator NewPitch = CameraBoom->GetComponentRotation();
	//	//we should discuss whether we should make player able to look at character closer :p
	////	NewPitch.Pitch = FMath::Clamp<float>(NewPitch.Pitch + CameraInput.Y, -90.0f, -90.0f);
	//	CameraBoom->SetWorldRotation(NewPitch);
	//
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(TEXT("%.5d", GetActorRotation())));
}

/*void ABaseCharacter::OnHurt()
{
	AddHealth(-60);
	//idk lol
}*/

void AMainCharacter::OnDeath() {

	CharacterID -= 1;

	//resets the CharacterID
	if (CharacterID < 0)
		CharacterID = 2;

	SetAnimatorOnDeath();
	SetCharacterStats();
	Health = 100;
}

void AMainCharacter::SetCharacterStats() {
	FTimerHandle UnusedHandle;
	if (CharacterID == 0) {// Demon
		//death animation
		UpdateAnimator();
		/*Knight->SetFlipbook(KnightDeath);
		
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this]() {
			IsDead = false;
			}, 0.f, false,0.2f);*/
		Knight->SetVisibility(false);
		/*
		Demon->SetFlipbook(DemonRunning);*/
		UpdateAnimator();
		Demon->SetVisibility(true);
		Health = 200;
		Speed = 1.4f;
		Damage = 100;
	}
	else if (CharacterID == 1) {// Knight
		//death animation
		UpdateAnimator();
		
		Angel->SetVisibility(false);
		//idle animation
		UpdateAnimator();
		
		Knight->SetVisibility(true);
		
		Health = 100;
		Speed = 1.0f;
		Damage = 10;
	}
	else if (CharacterID == 2) {// Angel
		//Death
		UpdateAnimator();

		Demon->SetVisibility(false);
		
		
		UpdateAnimator();
		Angel->SetVisibility(true);

		Health = 70;
		Speed = 1.5f;
		Damage = 7;
	}

	
}

void AMainCharacter::SpawnHitBox(float Damage, EHitBoxType HitBoxType)
{
	FActorSpawnParameters SpawnParameters;
	// reference from the internet 
	// AProjectileArrow* spawnedArrow = (AProjectileArrow*) GetWorld()->SpawnActor(AProjectileArrow::StaticClass(), NAME_None, &yourLocation);
	DamageBox = GetWorld()->SpawnActor<ADamageHitBox>(GetActorLocation(), GetActorRotation(),SpawnParameters);
	DamageBox->Initialize(Damage, GetActorLocation(), HitBoxType);
	DamageBox->VisualizeHitbox();
	//HitboxesArray.Add(HitBox);

	
}



void AMainCharacter::MoveForward(float Value)
{
	//normal movement speed
	if ((Controller != NULL) && (Value != 0.0f))
	{

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//running movement speed
		//THIS PART IS RUINING THE ROTATION!


		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		//left
		if (Value < 0)
		{
			SetActorRotation(FRotator(0.f,-180.f,0.f));
		}
		//right
		else {
			SetActorRotation(FRotator(0.f, 0.f, 0.f));
		}
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::Run()
{
	IsRunning = true;
	UpdateAnimator();
	this->GetCharacterMovement()->MaxWalkSpeed = Speed * 600.0f;
}

void AMainCharacter::StopRunning()
{
	IsRunning = false;
	UpdateAnimator();
	this->GetCharacterMovement()->MaxWalkSpeed = Speed * 300.0f;
}

//void AMainCharacter::OnAttack() {
//
//}

void AMainCharacter::Attack()
{
	IsAttacking = true;
	FTimerHandle UnusedHandle;
	//OnAttack maybe can call in collision boxes etc
	OnAttack();
	
	switch (CharacterID) {
		
	case 0:
		{	
		SpawnHitBox(Damage, EHitBoxType::HB_DEMON);
		}
		break;
	case 1:
		//Human
	{
		SpawnHitBox(Damage, EHitBoxType::HB_KNIGHT);
		
		//Knight->SetFlipbook(KnightAttacking);

		////GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMainCharacter::Attack, 0.1f, false);
		//GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this]() {
		//	IsAttacking = false;
		//	}, 0.f, false, 0.4f);
		//Knight->SetFlipbook(KnightRunning);
	}
		break;
	case 2:
		//Angel
	{	
		SpawnHitBox(Damage, EHitBoxType::HB_ANGEL);
	}break;
	}
	UpdateAnimator();
	IsAttacking = false;
	
	if (DamageBox->Destroy()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Destroyed Damageboxes! ");
	};
	
}

void AMainCharacter::StopAttacking()
{
	IsAttacking = false;
}

void AMainCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AMainCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void AMainCharacter::ZoomIn()
{
	bZoomingIn = true;
}

void AMainCharacter::ZoomOut()
{
	bZoomingIn = false;
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	//Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::StopRunning);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
	/*PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMainCharacter::StopAttacking);*/


	//Debug Switch
	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &AMainCharacter::OnDeath);
	



	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "MousePitch" handles devices that provide an absolute delta, such as a mouse.

	PlayerInputComponent->BindAxis("MousePitch", this, &AMainCharacter::PitchCamera);

	PlayerInputComponent->BindAxis("MouseYaw", this, &AMainCharacter::YawCamera);


	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMainCharacter::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &AMainCharacter::ZoomOut);
}
