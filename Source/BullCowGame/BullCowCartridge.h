// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	void SetupGame();
	void EndGame(bool Lost);
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	FString GetWordFromList(const TArray<FString>& List) const;
	TArray<FString> GetValidWords(const TArray<FString>& List) const;
	void GetBullCows(const FString& Guess, int32& Bulls, int32& Cows) const;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> ValidWords;
};
