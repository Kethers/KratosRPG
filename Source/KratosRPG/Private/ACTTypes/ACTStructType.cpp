// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "ACTTypes/ACTStructType.h"
#include "AbilitySystem/Abilities/ACTHeroGameplayAbility.h"

bool FACTHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}