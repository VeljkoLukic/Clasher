#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Units/BaseUnit.h"
#include "CardDataAsset.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8 { Unit, Spell };

UCLASS(BlueprintType)
class CLASHER_API UCardDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
    FText CardName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
    UTexture2D* CardArt = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
    ECardType CardType = ECardType::Unit;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card",
        meta = (ClampMin = 1, ClampMax = 9))
    int32 ElixirCost = 3;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Unit",
        meta = (EditCondition = "CardType == ECardType::Unit"))
    TSubclassOf<ABaseUnit> UnitClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Unit",
        meta = (EditCondition = "CardType == ECardType::Unit", ClampMin = 1))
    int32 SpawnCount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Spell",
        meta = (EditCondition = "CardType == ECardType::Spell"))
    float SpellDamage = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Spell",
        meta = (EditCondition = "CardType == ECardType::Spell"))
    float SpellRadius = 300.0f;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("CardData", GetFName());
    }
};