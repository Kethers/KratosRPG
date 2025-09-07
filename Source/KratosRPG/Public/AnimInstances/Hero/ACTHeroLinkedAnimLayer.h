// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ACTBaseAnimInstance.h"
#include "ACTHeroLinkedAnimLayer.generated.h"

class UACTHeroAnimInstance;
/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTHeroLinkedAnimLayer : public UACTBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UACTHeroAnimInstance* GetHeroAnimInstance() const;
};
