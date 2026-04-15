#include "Cards/CardPlaySubsystem.h"
#include "Core/ClasherPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Arena/TowerActor.h"
#include "Units/Components/UnitHealthComponent.h"

bool UCardPlaySubsystem::TryPlayCard(UCardDataAsset* CardData,
    const FVector& WorldPosition, EUnitTeam Team, APlayerState* Instigator)
{
    if (!CardData) return false;

    AClasherPlayerState* PS = Cast<AClasherPlayerState>(Instigator);
    if (!PS || !PS->SpendElixir(CardData->ElixirCost))
    {
        OnCardPlayFailed.Broadcast(CardData);
        return false;
    }

    if (CardData->CardType == ECardType::Unit)
        SpawnUnits(CardData, WorldPosition, Team);
    else
        CastSpell(CardData, WorldPosition, Team);

    OnCardPlayed.Broadcast(CardData, WorldPosition);
    return true;
}

void UCardPlaySubsystem::SpawnUnits(UCardDataAsset* CardData,
    const FVector& Location, EUnitTeam Team)
{
    if (!CardData->UnitClass) 
        return;

    const int32 Count = CardData->SpawnCount;
    const float Radius = 80.0f;

    for (int32 i = 0; i < Count; i++)
    {
        float Angle = (360.0f / Count) * i;
        float Rad = FMath::DegreesToRadians(Angle);
        FVector Offset = (Count > 1)
            ? FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0.f) * Radius
            : FVector::ZeroVector;

        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        ABaseUnit* Unit = GetWorld()->SpawnActor<ABaseUnit>(
            CardData->UnitClass, Location + Offset,
            FRotator::ZeroRotator, Params);

        if (Unit) 
            Unit->Deploy(Team, Location + Offset);
    }
}

void UCardPlaySubsystem::CastSpell(UCardDataAsset* CardData,
    const FVector& Location, EUnitTeam Team)
{
    TArray<AActor*> Units;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), Units);
    for (AActor* A : Units)
    {
        if (FVector::Dist(A->GetActorLocation(), Location) <= CardData->SpellRadius)
        {
            ABaseUnit* Unit = Cast<ABaseUnit>(A);
            if (Unit && Unit->Team != Team)
                Unit->GetHealthComponent()->ApplyDamage(CardData->SpellDamage, nullptr);
        }
    }
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerActor::StaticClass(), Towers);
    for (AActor* T : Towers)
    {
        ATowerActor* Tower = Cast<ATowerActor>(T);
        if (Tower && Tower->Team != Team &&
            FVector::Dist(T->GetActorLocation(), Location) <= CardData->SpellRadius)
            Tower->GetHealthComponent()->ApplyDamage(CardData->SpellDamage, nullptr);
    }
}