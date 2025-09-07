// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "ACTGameplayAbility.h"
#include "ACTHeroGameplayAbility.generated.h"

class UHeroUIComponent;
class AACTHeroCharacter;
class AACTHeroController;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTHeroGameplayAbility : public UACTGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ACT|Ability")
	AACTHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ACT|Ability")
	AACTHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ACT|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ACT|Ability")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ACT|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "ACT|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:
	TWeakObjectPtr<AACTHeroCharacter> CachedACTHeroCharacter;
	TWeakObjectPtr<AACTHeroController> CachedACTHeroController;
};
