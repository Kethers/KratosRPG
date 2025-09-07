// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ACTGameplayTags.h"
#include "ACTFunctionLibrary.h"
#include "Characters/ACTEnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "ACTDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	// TODO: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UACTFunctionLibrary::NativeDoesActorHaveTag(HitActor, ACTGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UACTFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), ACTGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UACTFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			ACTGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			ACTGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AACTEnemyCharacter* OwningEnemyPawn = GetOwningPawn<AACTEnemyCharacter>();

	check(OwningEnemyPawn);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyPawn->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyPawn->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
