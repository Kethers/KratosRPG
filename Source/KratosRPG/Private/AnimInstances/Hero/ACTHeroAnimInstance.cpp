// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "AnimInstances/Hero/ACTHeroAnimInstance.h"

#include "Characters/ACTHeroCharacter.h"

void UACTHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AACTHeroCharacter>(OwningCharacter);
	}
}

void UACTHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
