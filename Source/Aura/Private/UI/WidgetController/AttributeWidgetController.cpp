// Copyright Comrades


#include "UI/WidgetController/AttributeWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"


void UAttributeWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	
	for (auto& Pair :GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
	[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	);
	}
	
	GetAuraPS()->OnAttributePointChangeDelegate.AddLambda(
	[this](int32 NewAttributePoints)
		{
			AttributePointChangeDelegate.Broadcast(NewAttributePoints);
		}
	);
	
	AuraPlayerState->OnSpellPointsChangeDelegate.AddLambda(
	[this](int32 NewSpellPoints)
		{
			SpellPointChangeDelegate.Broadcast(NewSpellPoints);
		}
	);
}

void UAttributeWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	
	
	AttributePointChangeDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	
}

void UAttributeWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeWidgetController::BroadcastAttributeInfo(const FGameplayTag AttributeTag,
                                                        const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
