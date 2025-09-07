// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ACTTypes/ACTStructType.h"
#include "ACTAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "ACT|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FACTHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FACTHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle);

	UFUNCTION(BlueprintCallable, Category = "ACT|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "ACT|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
