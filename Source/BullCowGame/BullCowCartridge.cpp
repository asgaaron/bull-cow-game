// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/RandomStream.h"

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
        
        return;
    }
    SetupGame();
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
        return;
    }

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("The hidden word has %d characters..."), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The hidden word is an isogram..."));
        return;
    }

    PrintLine(TEXT("That guess wasn't right, guess again..."));
    GiveHint();
    Lives--;
    if (Lives == 0)
    {
        EndGame();
        return;
    }

    PrintLine(TEXT("Lives left: %d"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    TMap<char, int32> Charmap;
    for (char I : Word)
    {
        if (Charmap.Contains(I))
            return false;
        else
            Charmap.Add(I, 1);
    }
    return true;
}

void UBullCowCartridge::GiveHint() const
{
    int32 Index = FMath::RandRange(0, HiddenWord.Len() - 1);
    FString Position;
    switch (Index)
    {
        case 0: Position = "first"; break;
        case 1: Position = "second"; break;
        case 2: Position = "third"; break;
        case 3: Position = "fourth"; break;
    }
    PrintLine(TEXT("Here's a hint: the %s character is %c..."), *Position, HiddenWord[Index]);
}