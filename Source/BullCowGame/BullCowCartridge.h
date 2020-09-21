// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/RandomStream.h"
#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls, Cows;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString &Guess);
	bool IsIsogram(const FString &Input) const;
	void GiveHint() const;
	FBullCowCount GetBullCows(const FString &Guess) const;

private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Words;
};
