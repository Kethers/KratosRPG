#pragma once

UENUM()
enum class EACTConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EACTValidType : uint8
{
	Valid,
	Invalid,
};

UENUM()
enum class EACTSuccessType : uint8
{
	Successful,
	Failed,
};

UENUM()
enum class EACTCountDownActionInput : uint8
{
	Start,
	Cancel,
};

UENUM()
enum class EACTCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled,
};

UENUM(BlueprintType)
enum class EACTGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard,
};

UENUM(BlueprintType)
enum class EACTInputMode : uint8
{
	GameOnly,
	UIOnly,
};
