// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "DamageHitBox.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
	:Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetHiddenInGame(false);
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	
}

void ABaseCharacter::CheckIfDead()
{
	if (Health <= 0) {
		Health = 0;
		IsDead = true;
		OnDeath();
	}
	else
		IsDead = false;
}

void ABaseCharacter::AddHealth(float Delta)
{
	Health += Delta;
	CheckIfDead();
}

void ABaseCharacter::OnHurt(float Delta)
{
	
	AddHealth(-Delta);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damaged Health: %f"), Health));
	//idk lol
}

void ABaseCharacter::OnDeath()
{
	//idk lol
}

void ABaseCharacter:: OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this)) {
		//FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), GetWorld()->TimeSeconds)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Onbox getting overlapped Health: %f"), Health));
		//OnHurt(-20.f);
	}

}

//Severity	Code	Description	Project	File	Line	Suppression State
//Error	C2664	'void TSparseDynamicDelegate<FComponentHitSignature_MCSignature,UPrimitiveComponent,& `anonymous-namespace'::UPrimitiveComponentSparseOnComponentHitStr, FComponentHitSignatureOffsetGetter > ::__Internal_AddDynamic<ABaseCharacter>(UserClass*, void(__cdecl ABaseCharacter::*)(UPrimitiveComponent*, AActor*, UPrimitiveComponent*, FVector, const FHitResult&), FName)
//': cannot convert argument 2 from 'void(__cdecl ABaseCharacter::*)(UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)' to 'void(__cdecl ABaseCharacter::*)(UPrimitiveComponent*, AActor*, UPrimitiveComponent*, FVector, const FHitResult&)'	TemplarDefender	D:\All of My folders\Assignment\Unreal Project\TemplarDefender\Source\TemplarDefender\BaseCharacter.cpp	70	


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnBoxBeginOverlap);
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




