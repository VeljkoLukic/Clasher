#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindTarget.generated.h"

UCLASS()
class CLASHER_API UBTTask_FindTarget : public UBTTaskNode
{
    GENERATED_BODY()
public:
    UBTTask_FindTarget();

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetActorKey;

protected:
    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};