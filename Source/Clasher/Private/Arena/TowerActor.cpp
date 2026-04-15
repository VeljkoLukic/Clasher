#include "Arena/TowerActor.h"
#include "Units/Components/UnitHealthComponent.h"
#include "Units/Components/UnitCombatComponent.h"
#include "Kismet/GameplayStatics.h"

ATowerActor::ATowerActor()
{
    PrimaryActorTick.bCanEverTick = false;
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    HealthComponent = CreateDefaultSubobject<UUnitHealthComponent>(TEXT("Health"));
    HealthComponent->MaxHealth = 1000.0f;
    RootComponent = MeshComponent;
}

void ATowerActor::BeginPlay()
{
    Super::BeginPlay();
    HealthComponent->OnDied.AddDynamic(this, &ATowerActor::HandleDestroyed);
    GetWorldTimerManager().SetTimer(
        AttackTimer, this, &ATowerActor::AttackNearestEnemy, AttackRate, true);
}

void ATowerActor::AttackNearestEnemy()
{
    TArray<AActor*> Found;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), Found);

    EUnitTeam EnemyTeam = (Team == EUnitTeam::Player) ? EUnitTeam::Enemy : EUnitTeam::Player;
    float BestDist = AttackRange * AttackRange;
    ABaseUnit* Target = nullptr;

    for (AActor* A : Found)
    {
        ABaseUnit* Unit = Cast<ABaseUnit>(A);

        if (!Unit || Unit->Team != EnemyTeam) 
            continue;

        if (Unit->GetHealthComponent()->IsDead()) 
            continue;

        float D = FVector::DistSquared(GetActorLocation(), Unit->GetActorLocation());

        if (D < BestDist) 
        {
            BestDist = D; 
            Target = Unit; 
        }
    }

    if (Target)
        Target->GetHealthComponent()->ApplyDamage(AttackDamage, this);
}

void ATowerActor::HandleDestroyed()
{
    GetWorldTimerManager().ClearTimer(AttackTimer);
}