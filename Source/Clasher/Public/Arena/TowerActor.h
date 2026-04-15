#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Units/BaseUnit.h"
#include "TowerActor.generated.h"

UCLASS()
class CLASHER_API ATowerActor : public AActor
{
    GENERATED_BODY()
public:
    ATowerActor();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
    EUnitTeam Team = EUnitTeam::Enemy;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class UUnitHealthComponent> HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackDamage = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackRange = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float AttackRate = 1.0f;

    UFUNCTION(BlueprintPure, Category = "Tower")
    UUnitHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle AttackTimer;
    UFUNCTION() void AttackNearestEnemy();
    UFUNCTION() void HandleDestroyed();
};