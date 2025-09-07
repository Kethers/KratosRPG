// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "ACTWeaponBase.h"
#include "ACTTypes/ACTStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "ACTHeroWeapon.generated.h"

UCLASS()
class KRATOSRPG_API AACTHeroWeapon : public AACTWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FACTHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
