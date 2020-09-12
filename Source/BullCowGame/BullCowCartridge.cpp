// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    if (!bGameOver)
    {
        ProcessGuess(Input);
    }
    else
    {
        SetupGame();
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = "kale";
    Lives = 3;
    bGameOver = false;
    PrintLine(TEXT("Welcome to bulls and cows!\nGuess the %i letter word.\nType your guess and press enter..."), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("GAME OVER\nThe hidden word was: %s\nPress enter to continue..."), *HiddenWord);
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess.Equals(HiddenWord))
    {
        PrintLine(TEXT("NICE! You win!"));
        EndGame();
    }
    else
    {
        if (HiddenWord.Len() != Guess.Len())
        {
            PrintLine(TEXT("The hidden word has %d characters..."), HiddenWord.Len());
        }
        else
        {
            PrintLine(TEXT("That guess wasn't right, guess again..."));
            Lives--;
            if (Lives == 0)
            {
                EndGame();
            }
            else
            {
                PrintLine(TEXT("Lives left: %d"), Lives);
            }
        }
    }
}