// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Items/Weapons/ACTHeroWeapon.h"


void AACTHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AACTHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
