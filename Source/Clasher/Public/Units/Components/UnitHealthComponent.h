#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

UCLASS(ClassGroup = (Unit), meta = (BlueprintSpawnableComponent))
class CLASHER_API UUnitHealthComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UUnitHealthComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void ApplyDamage(float Damage, AActor* Instigator);

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category = "Health")
    bool IsDead() const { return bIsDead; }

    UPROPERTY(BlueprintAssignable) FOnHealthChanged OnHealthChanged;
    UPROPERTY(BlueprintAssignable) FOnDied OnDied;

protected:
    virtual void BeginPlay() override;

private:
    float CurrentHealth = 0.0f;
    bool  bIsDead = false;
};