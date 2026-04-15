#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

UCLASS()
class CLASHER_API AUnitAIController : public AAIController
{
    GENERATED_BODY()
public:
    AUnitAIController();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

protected:
    virtual void OnPossess(APawn* InPawn) override;
};