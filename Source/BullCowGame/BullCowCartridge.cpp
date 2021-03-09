// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

	if (bGameOver)
	{	
		ClearScreen();
		SetupGame();
	}
	else
	{

		ClearScreen();
		PrintLine(Input);

		if (Input == HiddenWord)
		{
			PrintLine(TEXT("Your guess was correct!\nPress Return to play again"));
			bGameOver = true;
		}
		else
		{
			--Lives;
			PrintLine(FString::Printf(TEXT("Your guess was wrong!\nLives Remaining: %d"), Lives));
			//decrement life; show remaining lives
			if (Lives > 0)
			{
				if (HiddenWord.Len() != Input.Len())
				{
					PrintLine(FString::Printf(TEXT("Hidden word is %d letters long. Try again!"), HiddenWord.Len()));
				}				
			}
			else
			{
				EndGame();
			}					
		}

		//check for isogram
		//check Bulls or Cows

		//promt to play again (check input)
		//if YES: play again, NO: quit
	}
}

void UBullCowCartridge::SetupGame()
{
	bGameOver = false;
	HiddenWord = TEXT("phone");
	Lives = HiddenWord.Len();

	PrintLine(TEXT("Welcome to the Bull Cow game"));
	PrintLine(FString::Printf(TEXT("Guess the %d-letter word. You have %i lives"), HiddenWord.Len(), Lives));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Game lost! Press Return to try again"));
}