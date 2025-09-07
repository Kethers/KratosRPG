// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Characters/ACTBaseCharacter.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "AbilitySystem/ACTAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
AACTBaseCharacter::AACTBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	ACTAbilitySystemComponent = CreateDefaultSubobject<UACTAbilitySystemComponent>(TEXT("ACTAbilitySystemComponent"));
	ACTAttributeSet = CreateDefaultSubobject<UACTAttributeSet>(TEXT("ACTAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AACTBaseCharacter::GetAbilitySystemComponent() const
{
	return GetACTAbilitySystemComponent();
}

UPawnCombatComponent* AACTBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AACTBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AACTBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ACTAbilitySystemComponent)
	{
		ACTAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

