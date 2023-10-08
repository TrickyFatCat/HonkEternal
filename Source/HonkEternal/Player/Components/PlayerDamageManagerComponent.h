// Made dy Titled Goose Team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerDamageManagerComponent.generated.h"

class UHealthComponent;
class UPlayerArmorComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HONKETERNAL_API UPlayerDamageManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerDamageManagerComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UHealthComponent> HealthComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UPlayerArmorComponent> ArmorComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0))
	double GlobalDamageModifier = 1.f;

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0))
	double ArmorDamageModifier = 0.3333333f;

	void ApplyDamage(const int32 DamageAmount) const;

	UFUNCTION()
	void HandleOnAnyDamageTaken(AActor* DamagedActor,
	                            float Damage,
	                            const class UDamageType* DamageType,
	                            class AController* InstigatedBy,
	                            AActor* DamageCauser);
};
