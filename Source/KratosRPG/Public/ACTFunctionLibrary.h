// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ACTTypes/ACTEnumTypes.h"
#include "ACTFunctionLibrary.generated.h"

class UACTGameInstance;
struct FGameplayEffectSpecHandle;
class UPawnCombatComponent;
class UACTAbilitySystemComponent;\
struct FScalableFloat;

/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UACTAbilitySystemComponent* NativeGetActASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EACTConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EACTValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category="ACT|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category="ACT|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category="ACT|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirection(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category="ACT|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime,
		EACTCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") EACTCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category="ACT|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UACTGameInstance* GetACTGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(EACTInputMode InInputMode, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary")
	static void SaveCurrentGameDifficulty(EACTGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category="ACT|FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(EACTGameDifficulty& OutSavedDifficulty);
};
