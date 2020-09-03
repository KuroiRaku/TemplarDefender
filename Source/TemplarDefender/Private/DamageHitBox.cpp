// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHitBox.h"
#include "Components/BoxComponent.h"
#include "BaseCharacter.h"

// Sets default values
ADamageHitBox::ADamageHitBox()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetHiddenInGame(false);
	
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	HitColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("HitMaterial"));
	DamageColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("ProximityMaterial"));
	Color = CreateDefaultSubobject<UMaterialInterface>(TEXT("NormalMaterial"));

	HitBox->SetMaterial(0, Color);
	
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageHitBox::OnOverlapBegin);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ADamageHitBox::OnOverlapEnd);

}

void ADamageHitBox::Initialize(float Damage, FVector Location, EHitBoxType HitBoxType)
{
	this->Damage = Damage;
	this->HitBoxLocation = Location;
	HitBoxLocation.Y += 100;
	this->HitBoxType = HitBoxType;
}

void ADamageHitBox::VisualizeHitbox()
{
	switch (HitBoxType)
	{
	case EHitBoxType::HB_ANGEL:
		{
		HitBox->SetWorldScale3D(FVector(0.1, 2, 8));
		HitBox->SetWorldLocation(HitBoxLocation);
		
		}break;
	case EHitBoxType::HB_KNIGHT:
		{
		HitBox->SetWorldScale3D(FVector(0.1, 2, 4));
		HitBox->SetWorldLocation(HitBoxLocation);

		}break;
	case EHitBoxType::HB_DEMON:
		{
		HitBox->SetWorldScale3D(FVector(0.1, 1, 1));
		HitBox->SetWorldLocation(HitBoxLocation);


		}break;
	}
	/*if (IfCollides)
	{
		HitBox->SetMaterial(0, HitColor);
	}*/
}

//bool ADamageHitBox::IfCollides()
//{
//	if (this->IsOverlappingActor(ABaseCharacter)) {
//		return true;
//	}
//	return false;
//}

void ADamageHitBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("We start"));
	}
}

void ADamageHitBox::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("We Ended"));
	}
}

