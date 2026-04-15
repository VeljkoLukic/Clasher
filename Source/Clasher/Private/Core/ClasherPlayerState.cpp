#include "Core/ClasherPlayerState.h"

AClasherPlayerState::AClasherPlayerState()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AClasherPlayerState::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(
        ElixirRegenTimer, this, &AClasherPlayerState::RegenElixir, 0.1f, true);
}

void AClasherPlayerState::RegenElixir()
{
    if (CurrentElixir < MaxElixir)
    {
        CurrentElixir = FMath::Min(CurrentElixir + 0.1f, MaxElixir);
        OnElixirChanged.Broadcast(CurrentElixir);
    }
}

bool AClasherPlayerState::SpendElixir(float Amount)
{
    if (CurrentElixir < Amount) 
        return false;

    CurrentElixir -= Amount;
    OnElixirChanged.Broadcast(CurrentElixir);
    return true;
}