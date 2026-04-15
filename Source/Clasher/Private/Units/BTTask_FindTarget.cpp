#include "Units/BTTask_FindTarget.h"
#include "Units/UnitAIController.h"
#include "Units/BaseUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Arena/TowerActor.h"
#include "Units/Components/UnitHealthComponent.h"
#include "Units/Components/UnitCombatComponent.h"

UBTTask_FindTarget::UBTTask_FindTarget()
{
    NodeName = "Find Nearest Enemy";
    TargetActorKey.AddObjectFilter(this,
        GET_MEMBER_NAME_CHECKED(UBTTask_FindTarget, TargetActorKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AUnitAIController* Controller = Cast<AUnitAIController>(OwnerComp.GetAIOwner());
    ABaseUnit* Unit = Controller ? Cast<ABaseUnit>(Controller->GetPawn()) : nullptr;
    if (!Unit) return EBTNodeResult::Failed;

    EUnitTeam EnemyTeam = (Unit->Team == EUnitTeam::Player)
        ? EUnitTeam::Enemy : EUnitTeam::Player;

    TArray<AActor*> All;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), All);

    TArray<AActor*> Enemies;
    for (AActor* A : All)
    {
        ABaseUnit* B = Cast<ABaseUnit>(A);
        if (B && B->Team == EnemyTeam && !B->GetHealthComponent()->IsDead())
            Enemies.Add(A);
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerActor::StaticClass(), All);
    for (AActor* A : All)
    {
        ATowerActor* T = Cast<ATowerActor>(A);
        if (T && T->Team == EnemyTeam) Enemies.Add(A);
    }

    AActor* Target = Unit->GetCombatComponent()->FindNearestTarget(Enemies);
    if (!Target) return EBTNodeResult::Failed;

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(
        TargetActorKey.SelectedKeyName, Target);
    return EBTNodeResult::Succeeded;
}