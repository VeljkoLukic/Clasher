#include "Units/UnitAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AUnitAIController::AUnitAIController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AUnitAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (BehaviorTreeAsset)
        RunBehaviorTree(BehaviorTreeAsset);
}