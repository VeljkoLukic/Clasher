#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ClasherPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElixirChanged, float, NewElixir);

UCLASS()
class CLASHER_API AClasherPlayerState : public APlayerState
{
    GENERATED_BODY()
public:
    AClasherPlayerState();

    UPROPERTY(BlueprintReadOnly, Category = "Elixir")
    float CurrentElixir = 5.0f;

    static constexpr float MaxElixir = 10.0f;

    UPROPERTY(BlueprintAssignable, Category = "Elixir|Events")
    FOnElixirChanged OnElixirChanged;

    UFUNCTION(BlueprintCallable, Category = "Elixir")
    bool SpendElixir(float Amount);

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle ElixirRegenTimer;

    UFUNCTION()
    void RegenElixir();
};