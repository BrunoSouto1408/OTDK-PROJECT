// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDamageSystemComponent.h"
#include "PlayerStatsComponent.h"

// Sets default values for this component's properties
UPlayerDamageSystemComponent::UPlayerDamageSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

float UPlayerDamageSystemComponent::CalculateDamage(
    EDamageType INDamageType,
    float MagicalDamage,
    float PhysicalDamage
    )
{
    bool bIsCritical = CriticalCheck();

    switch (INDamageType)
    {
        

    case EDamageType::Physical:
        if (bIsCritical)
        {
           
            float FinalMultiplier = 1.f;

            FinalMultiplier *= (PlayerStatsComponent->CriticalDamageMultiplier + PlayerStatsComponent->CriticalDamage);
            FinalMultiplier *= PlayerStatsComponent->AditionalDamageMultiplier;

            float FinalDamage = PhysicalDamage * FinalMultiplier;

            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Final Physical Critical Damage: %f"), FinalDamage));
            
            return FinalDamage;
        }
        else
        {
			float FinalDamage = PhysicalDamage* PlayerStatsComponent->AditionalDamageMultiplier;
            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Final Physical Normal Damage: %f"), FinalDamage));
            return FinalDamage;
        }

    case EDamageType::Magical:
        if (bIsCritical)
        {
            float FinalMultiplier = 1.f;

            FinalMultiplier *= (PlayerStatsComponent->CriticalDamageMultiplier + PlayerStatsComponent->CriticalDamage);
            FinalMultiplier *= PlayerStatsComponent->AditionalDamageMultiplier;

            float FinalDamage = MagicalDamage * FinalMultiplier;

            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("Final Magical Critical Damage: %f"), FinalDamage));

            return FinalDamage;
        }
        else
        {
            float FinalDamage = MagicalDamage * PlayerStatsComponent->AditionalDamageMultiplier;
            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage

            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT("Final Magical Normal Damage: %f"), FinalDamage));
            return FinalDamage;
        }

    case EDamageType::Mixed:
        if (bIsCritical)
        {
            float FinalMultiplier = 1.f;

            FinalMultiplier *= (PlayerStatsComponent->CriticalDamageMultiplier + PlayerStatsComponent->CriticalDamage);
            FinalMultiplier *= PlayerStatsComponent->AditionalDamageMultiplier;

            float FinalDamage = (MagicalDamage + PhysicalDamage) * FinalMultiplier;

            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Final Mixed Critical Damage: %f"), FinalDamage));

            return FinalDamage;
        }
        else
        {
            float FinalDamage = (MagicalDamage + PhysicalDamage) * PlayerStatsComponent->AditionalDamageMultiplier;

            FinalDamage = FMath::FRandRange(FinalDamage * 0.9f, FinalDamage * 1.3f); // Add some randomness to the final damage
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor:: Blue, FString::Printf(TEXT("Final Mixed Critical Damage: %f"), FinalDamage));

			return FinalDamage;
        }

    default:
        return 0.f;
    }
}

bool UPlayerDamageSystemComponent::CriticalCheck()
{

	float RandomValue = FMath::FRandRange(0.f, 1.f);

	if (RandomValue <= PlayerStatsComponent->CriticalChance)
	{
		
		return true;
	}
	else
	{
		
		return false;
	}
}

void UPlayerDamageSystemComponent::BeginPlay()
{
    Super::BeginPlay();
    // ...

    PlayerStatsComponent = GetOwner()->FindComponentByClass<UPlayerStatsComponent>();

    if (!PlayerStatsComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerStatsComponent not found!"));
    }
}