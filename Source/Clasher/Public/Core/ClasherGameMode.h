#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClasherGameMode.generated.h"

UENUM(BlueprintType)
enum class EMatchPhase : uint8
{
    WaitingToStart,
    InProgress,
    OvertimeWarning,
    Overtime,
    MatchEnded
};

UCLASS()
class CLASHER_API AClasherGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    AClasherGameMode();

    UFUNCTION(BlueprintCallable, Category = "Match")
    void TransitionToPhase(EMatchPhase NewPhase);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
};