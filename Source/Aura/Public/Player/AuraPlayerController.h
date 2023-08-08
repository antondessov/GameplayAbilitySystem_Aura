// Copyright Comrades

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay();
	
private:
	UPROPERTY(EditAnywhere, Category = "")
	TObjectPtr<UInputMappingContext> AuraContext;
};
