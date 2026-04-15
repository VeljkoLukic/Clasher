#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Cards/CardDataAsset.h"
#include "Units/BaseUnit.h"
#include "CardPlaySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardPlayed,
    UCardDataAsset*, Card, FVector, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardPlayFailed,
    UCardDataAsset*, Card);

UCLASS()
class CLASHER_API UCardPlaySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Cards")
    bool TryPlayCard(UCardDataAsset* CardData, const FVector& WorldPosition,
        EUnitTeam Team, APlayerState* Instigator);

    UPROPERTY(BlueprintAssignable) FOnCardPlayed     OnCardPlayed;
    UPROPERTY(BlueprintAssignable) FOnCardPlayFailed OnCardPlayFailed;

private:
    void SpawnUnits(UCardDataAsset* CardData, const FVector& Location, EUnitTeam Team);
    void CastSpell(UCardDataAsset* CardData, const FVector& Location, EUnitTeam Team);
};