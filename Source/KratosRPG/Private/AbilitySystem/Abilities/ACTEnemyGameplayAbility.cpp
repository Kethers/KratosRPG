// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "AbilitySystem/Abilities/ACTEnemyGameplayAbility.h"
#include "Characters/ACTEnemyCharacter.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "ACTGameplayTags.h"

AACTEnemyCharacter* UACTEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedACTEnemyCharacter.IsValid())
	{
		CachedACTEnemyCharacter = Cast<AACTEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedACTEnemyCharacter.IsValid() ? CachedACTEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UACTEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UACTEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		ACTGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}
