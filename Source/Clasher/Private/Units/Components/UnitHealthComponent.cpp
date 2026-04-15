#include "Units/Components/UnitHealthComponent.h"

UUnitHealthComponent::UUnitHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUnitHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UUnitHealthComponent::ApplyDamage(float Damage, AActor* Instigator)
{
    if (bIsDead || Damage <= 0.0f) 
        return;

    CurrentHealth = FMath::Max(0.0f, CurrentHealth - Damage);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

    if (CurrentHealth == 0.0f)
    {
        bIsDead = true;
        OnDied.Broadcast();
    }
}

float UUnitHealthComponent::GetHealthPercent() const
{
    return MaxHealth > 0.f ? CurrentHealth / MaxHealth : 0.0f;
}