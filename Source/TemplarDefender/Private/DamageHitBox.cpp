// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHitBox.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BaseCharacter.h"
#include "MainCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "VainCrystal.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"


// Sets default values
ADamageHitBox::ADamageHitBox()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	RootComponent = HitBox;
	/*HitBox->SetupAttachment(RootComponent);*/
	HitBox->SetHiddenInGame(false);
	
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	


	//HitColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("HitMaterial"));
	//HitColor = (UMaterialInterface* )UMaterialInstanceDynamic::Create(StoredMaterial, this);

	//old method doesn't work :(
	/*ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial2(TEXT("/Game/Material/Red.Red"));

	if (FoundMaterial2.Succeeded())
	{
		UMaterialInstanceDynamic* DynamicMaterialInstance2 = UMaterialInstanceDynamic::Create(FoundMaterial2.Object, this);
		UE_LOG(LogTemp, Warning, TEXT("Found damage color aka red"));
		DamageColor = (UMaterialInterface*)DynamicMaterialInstance2;
	}*/


	
	//DamageColor = (UMaterialInterface*)UMaterialInstanceDynamic::Create(StoredMaterial, this);

	/*HitColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("HitMaterial"));
	DamageColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("DamageMaterial"));
	*/
	Color = CreateDefaultSubobject<UMaterialInterface>(TEXT("NormalMaterial"));

	HitColor = HitBox->CreateDynamicMaterialInstance(0);
	if (HitColor != nullptr)
	{
		HitColor->SetVectorParameterValue(FName("blue"),FLinearColor(0.f,0.f,1.f,0.f));
	}
	//HitBox->SetMaterial(0, HitColor);
	
	
	//HitBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageHitBox::OnOverlapBegin);
	//HitBox->OnComponentEndOverlap.AddDynamic(this, &ADamageHitBox::OnOverlapEnd);

}

void ADamageHitBox::Initialize(float Damage, FVector Location, EHitBoxType HitBoxType)
{
	this->Damage = Damage;
	this->HitBoxLocation = Location;
	this->HitBoxType = HitBoxType;
}

void ADamageHitBox::VisualizeHitbox()
{
	HitBox->SetMaterial(0, HitColor);
	/*HitBoxLocation.Y += 200.f;*/
	switch (HitBoxType)
	{
	case EHitBoxType::HB_ANGEL:
		{
		HitBox->SetWorldScale3D(FVector(0.5, 8, 2));
		HitBox->SetWorldLocation(HitBoxLocation);
		
		}break;
	case EHitBoxType::HB_KNIGHT:
		{
		HitBox->SetWorldScale3D(FVector(0.5, 3, 4));
		HitBox->SetWorldLocation(HitBoxLocation);

		}break;
	case EHitBoxType::HB_DEMON:
		{
		HitBox->SetWorldScale3D(FVector(0.5, 3, 1));
		HitBox->SetWorldLocation(HitBoxLocation);


		}break;
	default:
	{
		HitBox->SetWorldScale3D(FVector(0.5, 1, 1));
		HitBox->SetWorldLocation(HitBoxLocation);
	}break;
	}
	//DrawDebugBox(GetWorld(), HitBoxLocation, GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, 2, 0, 5);
	if (IfCollides())
	{
		//DrawDebugBox(GetWorld(), HitBoxLocation, GetComponentsBoundingBox().GetExtent(), FColor::Red, true, 2, 0, 5);
		DamageColor = HitBox->CreateDynamicMaterialInstance(0);
				if (DamageColor != nullptr)
				{
					DamageColor->SetVectorParameterValue(FName("red"), FLinearColor(1.f, 0.f, 0.f, 0.f));
				}
	}
}

bool ADamageHitBox::IfCollides()
{
	TArray<AActor*> Enemy;
	GetOverlappingActors(Enemy, TSubclassOf<ABaseCharacter>());

	if (Enemy.Max()<=0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("No enemy found")));
		return false;
	}
	else {
		//For every enemy in the array that it overlaps, it will deal damage by calling the onhurt function
		if (IsDamaging) {
			for (auto enemy : Enemy)
			{
				ABaseCharacter* Object = Cast<ABaseCharacter>(enemy);
				if (Object)
				{
					Object->OnHurt(Damage);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DamageHitBoxes Detected other actors And deals: %f"), Damage));
				}
				AVainCrystal* Crystal = Cast<AVainCrystal>(enemy);
				if (Crystal)
				{
					Crystal->OnHurt(Damage);
					AMainCharacter* const TemporaryCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
					TemporaryCharacter->HurtCrystal(Damage);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DamageHitBoxes Detected Crystal And deals: %f"), Damage));
				}

			}
		}
	}
	
	return true;
}

//void ADamageHitBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	// check if Actors do not equal nullptr
//	//ABaseCharacter TestObject = Cast<ABaseCharacter>(OtherActor);
//	if (OtherActor && (OtherActor != this) && Cast<ABaseCharacter>(OtherActor))
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DamageHitBoxes Detected other actors ")));
//		Cast<ABaseCharacter>(OtherActor)->OnHurt(Damage);
//		DrawDebugBox(GetWorld(), HitBoxLocation, GetComponentsBoundingBox().GetExtent(), FColor::Red, true, 2, 0, 5);
//		
//	}
//}
//
//void ADamageHitBox::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor && (OtherActor != this) && Cast<ABaseCharacter>(OtherActor))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("We Ended"));
//	}
//}

void ADamageHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

