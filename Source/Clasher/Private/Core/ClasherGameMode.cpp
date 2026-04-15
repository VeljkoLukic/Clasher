#include "Core/ClasherGameMode.h"
#include "Core/ClasherGameState.h"

AClasherGameMode::AClasherGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.5f;
    GameStateClass = AClasherGameState::StaticClass();
}

void AClasherGameMode::BeginPlay()
{
    Super::BeginPlay();
    TransitionToPhase(EMatchPhase::WaitingToStart);
}

void AClasherGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AClasherGameState* GS = GetGameState<AClasherGameState>();

    if (!GS || GS->MatchPhase != EMatchPhase::InProgress) 
        return;

    GS->RemainingTime -= DeltaSeconds * PrimaryActorTick.TickInterval / DeltaSeconds;

    if (GS->RemainingTime <= 0.0f) 
        TransitionToPhase(EMatchPhase::MatchEnded);

    else if (GS->RemainingTime <= 60.0f) 
        TransitionToPhase(EMatchPhase::OvertimeWarning);
}

void AClasherGameMode::TransitionToPhase(EMatchPhase NewPhase)
{
    AClasherGameState* GS = GetGameState<AClasherGameState>();

    if (GS) 
    { 
        GS->MatchPhase = NewPhase; 
        GS->OnMatchPhaseChanged.Broadcast(NewPhase); 
    }
}