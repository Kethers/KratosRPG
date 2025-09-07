// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Interfaces/PawnUIInterface.h"


// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.
UHeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
	return nullptr;
}

UEnemyUICompoent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
