// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Items/PickUps/ACTStoneBase.h"

#include "Characters/ACTHeroCharacter.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "ACTGameplayTags.h"

void AACTStoneBase::Consume(UACTAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void AACTStoneBase::OnPickUpCollectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
														 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AACTHeroCharacter* OverlappedHeroCharacter = Cast<AACTHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetACTAbilitySystemComponent()->TryActivateAbilityByTag(ACTGameplayTags::Player_Ability_PickUp_Stones);
	}
}
