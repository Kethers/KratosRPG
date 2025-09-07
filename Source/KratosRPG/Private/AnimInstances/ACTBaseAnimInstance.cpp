// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "KratosRPG/Public/AnimInstances/ACTBaseAnimInstance.h"
#include "ACTFunctionLibrary.h"

bool UACTBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UACTFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
