// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombatInterface.generated.h"

class UPawnCombatComponent;

// This class does not need to be modified.
UINTERFACE()
class UPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KRATOSRPG_API IPawnCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnCombatComponent* GetPawnCombatComponent() const = 0;
};
