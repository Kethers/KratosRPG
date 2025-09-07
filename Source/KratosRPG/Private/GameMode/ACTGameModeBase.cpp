// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "GameMode/ACTGameModeBase.h"

AACTGameModeBase::AACTGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
