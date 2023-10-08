// Made dy Titled Goose Team


#include "BaseEntityResource.h"


UBaseEntityResource::UBaseEntityResource()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBaseEntityResource::BeginPlay()
{
	CurValue = MaxValue;
	Super::BeginPlay();
}

double UBaseEntityResource::GetRelativeCurValue() const
{
	const double Result = MaxValue <= 0 ? 0.f : static_cast<double>(CurValue) / static_cast<double>(MaxValue);
	return Result;
}

bool UBaseEntityResource::IncreaseValue(const int32 Amount, const bool bClampToMax)
{
	if (Amount <= 0 || (bClampToMax && CurValue >= MaxValue))
	{
		return false;
	}

	CurValue += Amount;
	CurValue = bClampToMax ? FMath::Min(CurValue, MaxValue) : CurValue;
	
	OnValueChanged.Broadcast();
	OnValueIncreased.Broadcast(CurValue, MaxValue, GetRelativeCurValue(), Amount);

	return true;
}

bool UBaseEntityResource::DecreaseValue(const int32 Amount)
{
	if (Amount <= 0 || CurValue <= 0)
	{
		return false;
	}

	CurValue -= Amount;
	CurValue = FMath::Max(CurValue, 0);

	OnValueChanged.Broadcast();
	OnValueDecreased.Broadcast(CurValue, MaxValue, GetRelativeCurValue(), Amount);

	if (CurValue <= 0)
	{
		OnValueZero.Broadcast();
	}
	
	return true;
}
