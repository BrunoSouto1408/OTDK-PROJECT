#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerDamageSystemComponent.generated.h"


class UPlayerStatsComponent;

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    Physical UMETA(DisplayName = "Physical"),
    Magical UMETA(DisplayName = "Magical"),
    Mixed UMETA(DisplayName = "Mixed")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OTDK_API UPlayerDamageSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPlayerDamageSystemComponent();

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float CalculateDamage(EDamageType INDamageType,
        float MagicalDamage, 
        float PhysicalDamage
        );

	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool CriticalCheck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageType DamageType;

protected:
	virtual void BeginPlay() override;

	UPlayerStatsComponent* PlayerStatsComponent;
};