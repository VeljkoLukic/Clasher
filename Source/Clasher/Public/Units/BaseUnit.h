#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseUnit.generated.h"

UENUM(BlueprintType)
enum class EUnitTeam : uint8 { Player, Enemy };

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitAttacked, AActor*, Target);

UCLASS(Abstract)
class CLASHER_API ABaseUnit : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
    ABaseUnit();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit")
    EUnitTeam Team = EUnitTeam::Player;

    UFUNCTION(BlueprintCallable, Category = "Unit")
    void Deploy(EUnitTeam InTeam, const FVector& SpawnLocation);

    UFUNCTION(BlueprintPure, Category = "Unit")
    UUnitCombatComponent* GetCombatComponent() const { return CombatComponent; }

    UFUNCTION(BlueprintPure, Category = "Unit")
    UUnitHealthComponent* GetHealthComponent() const { return HealthComponent; }

    UPROPERTY(BlueprintAssignable, Category = "Unit|Events") FOnUnitDied     OnUnitDied;
    UPROPERTY(BlueprintAssignable, Category = "Unit|Events") FOnUnitAttacked OnUnitAttacked;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class UUnitHealthComponent> HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class UUnitCombatComponent> CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "Unit") void OnDeployed();
    UFUNCTION(BlueprintImplementableEvent, Category = "Unit") void OnDeath();

private:
    UFUNCTION() void HandleDeath();
    UFUNCTION() void HandleAttacked(AActor* Target);
};