// Copyright Comrades

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/**Combat Interface */
	virtual int32 GetPlayerLevel();
	/** end Combat Interface */

	/**Player Interface */
	virtual void AddToXP_Implementation(int32 InXP) override;
	/**End Player Interface */
	
private:
	virtual void InitAbilityActorInfo() override;
};
