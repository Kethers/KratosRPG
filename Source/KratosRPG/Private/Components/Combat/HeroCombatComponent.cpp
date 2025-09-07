// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/ACTHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ACTGameplayTags.h"

#include "ACTDebugHelper.h"

AACTHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AACTHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AACTHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AACTHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ACTGameplayTags::Shared_Event_MeleeHit,
		Data	
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ACTGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ACTGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}
