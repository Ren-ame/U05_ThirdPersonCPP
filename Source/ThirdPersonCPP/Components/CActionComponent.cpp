#include "CActionComponent.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCActionComponent::SetUnaremdMode()
{
}

void UCActionComponent::SetFistMode()
{
}

void UCActionComponent::SetOneHandMode()
{
}

void UCActionComponent::SetTwoHandMode()
{
}

void UCActionComponent::SetMagicBallMode()
{
}

void UCActionComponent::SetWarpMode()
{
}

void UCActionComponent::SetWhirlwindMode()
{
}

void UCActionComponent::SetMode(EActionType InNewType)
{
}

void UCActionComponent::ChageType(EActionType InNewType)
{
	EActionType Prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.Broadcast(Prev, InNewType);
	}
}
