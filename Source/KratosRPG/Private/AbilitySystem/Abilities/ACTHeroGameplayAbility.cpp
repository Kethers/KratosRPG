// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "AbilitySystem/Abilities/ACTHeroGameplayAbility.h"
#include "Characters/ACTHeroCharacter.h"
#include "Controllers/ACTHeroController.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "ACTGameplayTags.h"

AACTHeroCharacter* UACTHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedACTHeroCharacter.IsValid())
	{
		CachedACTHeroCharacter = Cast<AACTHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedACTHeroCharacter.IsValid() ? CachedACTHeroCharacter.Get() : nullptr;
}

AACTHeroController* UACTHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedACTHeroController.IsValid())
	{
		CachedACTHeroController = Cast<AACTHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedACTHeroController.IsValid() ? CachedACTHeroController.Get() : nullptr;
}

UHeroCombatComponent* UACTHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

UHeroUIComponent* UACTHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle UACTHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetACTAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	auto AvatarActor = GetAvatarActorFromActorInfo();
	ContextHandle.AddSourceObject(AvatarActor);
	ContextHandle.AddInstigator(AvatarActor, AvatarActor);

	FGameplayEffectSpecHandle EffectSpecHandle = GetACTAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(ACTGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}

bool UACTHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime,
	float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid())

	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray<TPair<float,float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}

	return RemainingCooldownTime > 0.f;
}
