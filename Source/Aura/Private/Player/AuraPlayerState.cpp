// Copyright Comrades


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f; // faster update, because PlayerState is slower
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::SetXP(const int32 InXP)
{
	XP = InXP;
	OnXpChangeDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetLevel(const int32 InLevel)
{
	Level = InLevel;
	OnLevelChangeDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetAttributePoints(const int32 InAttributePoints)
{
	AttributePoints = InAttributePoints;
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::SetSpellPoints(const int32 InSpellPoints)
{
	SpellPoints = InSpellPoints;
	OnSpellPointsChangeDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddToXP(const int32 InXP)
{
	XP += InXP;
	OnXpChangeDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToLevel(const int32 InLevel)
{
	Level += InLevel;
	OnLevelChangeDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToAttributePoints(const int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(const int32 InSpellPoints)
{
	SpellPoints += InSpellPoints;
	OnSpellPointsChangeDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangeDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXpChangeDelegate.Broadcast(XP); 
}

void AAuraPlayerState::OnRep_AttributePoint(int32 OldAttributePoints)
{
	OnAttributePointChangeDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangeDelegate.Broadcast(SpellPoints);
}
