// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Controllers/ACTHeroController.h"

AACTHeroController::AACTHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AACTHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}
