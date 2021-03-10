// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWords.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	ValidWords = GetValidWords(Words);
	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

	ClearScreen();
	if (bGameOver)
	{	
		SetupGame();
		return;
	}
	
	PrintLine(Input);
	ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
	bGameOver = false;
	HiddenWord = GetWordFromList(ValidWords);
	//PrintLine(TEXT("Chosen word: %s"), *HiddenWord);
	Lives = HiddenWord.Len();

	PrintLine(TEXT("Welcome to the Bull Cow game"));
	PrintLine(FString::Printf(TEXT("Guess the %d-letter word. You have %i lives"), HiddenWord.Len(), Lives));
}

void UBullCowCartridge::EndGame(bool Lost)
{
	FString message = Lost ? FString::Printf(TEXT("Game lost! Hidden word was \"%s\""), *HiddenWord) : TEXT("You guessed it correctly!");
	PrintLine(message);
	bGameOver = true;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	//Check for a match
	if (Guess == HiddenWord)
	{
		EndGame(false);
		return;
	}

	//End game and return if out of lives
	if (Lives <= 0)
	{
		EndGame(true);
		return;
	}

	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(FString::Printf(TEXT("Hidden word is %d letters long. Try again!"), HiddenWord.Len()));
		return;
	}

	//check for isogram
	if (!IsIsogram(Guess))
	{
		PrintLine(FString::Printf(TEXT("\"%s\" is not an isogram. Try again!"), *Guess));
		return;
	}
	
	//check Bulls or Cows
	int32 Bulls, Cows;
	GetBullCows(Guess, Bulls, Cows);
	PrintLine(TEXT("Bulls: %i, Cows: %i"), Bulls, Cows);
	if (Bulls > 0 || Cows > 0)
	{
		return;
	}

	//Decrement a life; show remaining lives
	--Lives;
	PrintLine(FString::Printf(TEXT("Your guess was wrong!\nLives Remaining: %d"), Lives));

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for (int32 Index = 0; Index < Word.Len() - 1; Index++)
	{
		for (int32 Next = Index + 1; Next < Word.Len(); Next++)
		{
			if (Word[Next] == Word[Index])
			{
				return false;
			}
		}
	}
	return true;
}

FString UBullCowCartridge::GetWordFromList(const TArray<FString>& List) const
{
	int32 Index = FMath::RandRange(0, List.Num()-1);
	return List[Index];
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& List) const
{
	TArray<FString> ValidWords;
	for (FString Word : List)
	{
		if (IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}
	return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& Bulls, int32& Cows) const
{
	Bulls = 0;
	Cows = 0;
	for (int32 Index = 0; Index < Guess.Len(); Index++)
	{
		if (Guess[Index] == HiddenWord[Index])
		{
			Bulls++;
		}
		else
		{
			for (int32 Other = 0; Other < Guess.Len(); Other++)
			{
				if (Other != Index)
				{
					if (Guess[Index] == HiddenWord[Other])
					{
						Cows++;
					}
				}
			}
		}
	}
}