// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "ACTGameplayAbility.h"
#include "ACTEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AACTEnemyCharacter;
/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTEnemyGameplayAbility : public UACTGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="ACT|Ability")
	AACTEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="ACT|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="ACT|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<AACTEnemyCharacter> CachedACTEnemyCharacter;
};
