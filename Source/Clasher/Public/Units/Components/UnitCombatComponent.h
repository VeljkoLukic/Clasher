#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttacked, AActor*, Target);

UCLASS(ClassGroup = (Unit), meta = (BlueprintSpawnableComponent))
class CLASHER_API UUnitCombatComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UUnitCombatComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackDamage = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackRange = 150.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackCooldown = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bCanTargetGround = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bCanTargetAir = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TEnumAsByte<ECollisionChannel> TargetChannel = ECC_Pawn;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    AActor* FindNearestTarget(const TArray<AActor*>& Candidates) const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TryAttack(AActor* Target);

    UPROPERTY(BlueprintAssignable) FOnAttacked OnAttacked;

private:
    FTimerHandle CooldownTimer;
    bool bReadyToAttack = true;

    UFUNCTION() void ResetAttackCooldown() { bReadyToAttack = true; }
};