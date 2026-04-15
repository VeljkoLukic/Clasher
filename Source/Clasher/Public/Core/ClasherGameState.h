#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Core/ClasherGameMode.h"
#include "ClasherGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchPhaseChanged, EMatchPhase, NewPhase);

UCLASS()
class CLASHER_API AClasherGameState : public AGameStateBase
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly, Category = "Match")
    EMatchPhase MatchPhase = EMatchPhase::WaitingToStart;

    UPROPERTY(BlueprintReadOnly, Category = "Match")
    float RemainingTime = 180.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Match")
    float PlayerTowerHP = 1000.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Match")
    float EnemyTowerHP = 1000.0f;

    UPROPERTY(BlueprintAssignable, Category = "Match|Events")
    FOnMatchPhaseChanged OnMatchPhaseChanged;
};