// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "AnimInstances/Hero/ACTHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/ACTHeroAnimInstance.h"

UACTHeroAnimInstance* UACTHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UACTHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
