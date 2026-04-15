#include "Units/BaseUnit.h"
#include "Units/Components/UnitHealthComponent.h"
#include "Units/Components/UnitCombatComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseUnit::ABaseUnit()
{
    PrimaryActorTick.bCanEverTick = false;

    HealthComponent = CreateDefaultSubobject<UUnitHealthComponent>(TEXT("Health"));
    CombatComponent = CreateDefaultSubobject<UUnitCombatComponent>(TEXT("Combat"));
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 0.0f;
    bUseControllerRotationYaw = false;
}

void ABaseUnit::BeginPlay()
{
    Super::BeginPlay();
    HealthComponent->OnDied.AddDynamic(this, &ABaseUnit::HandleDeath);
    CombatComponent->OnAttacked.AddDynamic(this, &ABaseUnit::HandleAttacked);
}

UAbilitySystemComponent* ABaseUnit::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void ABaseUnit::Deploy(EUnitTeam InTeam, const FVector& SpawnLocation)
{
    Team = InTeam;
    SetActorLocation(SpawnLocation);
    OnDeployed();
}

void ABaseUnit::HandleDeath()
{
    OnDeath();
    OnUnitDied.Broadcast();

    SetActorEnableCollision(false);
    GetCharacterMovement()->StopMovementImmediately();
}

void ABaseUnit::HandleAttacked(AActor* Target)
{
    OnUnitAttacked.Broadcast(Target);
}