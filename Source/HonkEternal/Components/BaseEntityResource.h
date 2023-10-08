// Made dy Titled Goose Team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseEntityResource.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValueChangedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValueZeroSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnValueIncreasedSignature,
                                              int32, CurValue,
                                              int32, MaxValue,
                                              double, RelativeCurValue,
                                              int32, DeltaValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnValueDecreasedSignature,
                                              int32, CurValue,
                                              int32, MaxValue,
                                              double, RelativeCurValue,
                                              int32, DeltaValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HONKETERNAL_API UBaseEntityResource : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseEntityResource();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnValueChangedSignature OnValueChanged;

	UPROPERTY(BlueprintAssignable)
	FOnValueZeroSignature OnValueZero;

	UPROPERTY(BlueprintAssignable)
	FOnValueIncreasedSignature OnValueIncreased;

	UPROPERTY(BlueprintAssignable)
	FOnValueDecreasedSignature OnValueDecreased;
	
	UFUNCTION(BlueprintGetter)
	int32 GetCurValue() const { return CurValue; }

	UFUNCTION(BlueprintGetter)
	int32 GetMaxValue() const { return MaxValue; }

	UFUNCTION(BlueprintPure)
	double GetRelativeCurValue() const;

	UFUNCTION(BlueprintCallable)
	bool IncreaseValue(const int32 Amount, const bool bClampToMax = true);

	UFUNCTION(BlueprintCallable)
	bool DecreaseValue(const int32 Amount);

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurValue)
	int32 CurValue = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetMaxValue, meta=(ClampMin=0))
	int32 MaxValue = 100;
};
