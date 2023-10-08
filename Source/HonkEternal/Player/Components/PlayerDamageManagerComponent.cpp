// Made dy Titled Goose Team


#include "PlayerDamageManagerComponent.h"

#include "PlayerArmorComponent.h"
#include "HonkEternal/Components/HealthComponent.h"


UPlayerDamageManagerComponent::UPlayerDamageManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPlayerDamageManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();
	ArmorComponent = GetOwner()->FindComponentByClass<UPlayerArmorComponent>();

	if (ensureMsgf(HealthComponent && ArmorComponent,
	               TEXT("PlayerDamageManager component can't find Health and/or Armor components in %s"),
	               *GetOwner()->GetName()))
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UPlayerDamageManagerComponent::HandleOnAnyDamageTaken);
	}
}

void UPlayerDamageManagerComponent::ApplyDamage(const int32 DamageAmount) const
{
	if (!HealthComponent || !ArmorComponent)
	{
		return;
	}

	int32 CurrentDamage = DamageAmount;

	if (ArmorComponent->GetCurValue() > 0)
	{
		CurrentDamage -= DamageAmount * ArmorDamageModifier;
		ArmorComponent->DecreaseValue(DamageAmount * ArmorDamageModifier);
	}

	HealthComponent->DecreaseValue(CurrentDamage);
}

void UPlayerDamageManagerComponent::HandleOnAnyDamageTaken(AActor* DamagedActor,
                                                           float Damage,
                                                           const UDamageType* DamageType,
                                                           AController* InstigatedBy,
                                                           AActor* DamageCauser)
{
	Damage *= GlobalDamageModifier;
	ApplyDamage(FMath::CeilToInt32(Damage));
}
