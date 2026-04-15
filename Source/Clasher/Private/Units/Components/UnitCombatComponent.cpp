#include "Units/Components/UnitCombatComponent.h"
#include "Units/Components/UnitHealthComponent.h"

UUnitCombatComponent::UUnitCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

AActor* UUnitCombatComponent::FindNearestTarget(const TArray<AActor*>& Candidates) const
{
    AActor* Nearest = nullptr;
    float NearestDist = FLT_MAX;
    const FVector MyLoc = GetOwner()->GetActorLocation();

    for (AActor* Candidate : Candidates)
    {
        if (!Candidate) 
            continue;

        UUnitHealthComponent* HP = Candidate->FindComponentByClass<UUnitHealthComponent>();

        if (HP && HP->IsDead()) 
            continue;

        float Dist = FVector::DistSquared(MyLoc, Candidate->GetActorLocation());

        if (Dist < NearestDist) 
        { 
            NearestDist = Dist; 
            Nearest = Candidate; 
        }
    }
    return Nearest;
}

void UUnitCombatComponent::TryAttack(AActor* Target)
{
    if (!Target || !bReadyToAttack) 
        return;

    UUnitHealthComponent* HP = Target->FindComponentByClass<UUnitHealthComponent>();

    if (!HP || HP->IsDead()) 
        return;

    HP->ApplyDamage(AttackDamage, GetOwner());
    OnAttacked.Broadcast(Target);

    bReadyToAttack = false;
    GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UUnitCombatComponent::ResetAttackCooldown, AttackCooldown, false);
}