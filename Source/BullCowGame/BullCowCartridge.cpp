// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/RandomStream.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Containers/UnrealString.h"
#include "Misc/Char.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Words, *WordListPath, [this](const FString &Word) { return UBullCowCartridge::IsIsogram(Word); });
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
    int32 RandomIndex = FMath::RandRange(0, Words.Num() - 1);
    HiddenWord = Words[RandomIndex];
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to bulls and cows!\nGuess the %i letter word.\nType your guess and press enter..."), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("GAME OVER\nThe hidden word was: %s\nPress enter to continue..."), *HiddenWord);
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
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

    Lives--;
    if (Lives == 0)
    {
        EndGame();
        return;
    }

    FBullCowCount Count = GetBullCows(Guess);
    PrintLine(TEXT("You have %i bulls and %i cows"), Count.Bulls, Count.Cows);
    PrintLine(TEXT("That guess wasn't right, you lost a life!"));
    PrintLine(TEXT("Lives left: %d"), Lives);
    GiveHint();
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
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
    case 0:
        Position = "first";
        break;
    case 1:
        Position = "second";
        break;
    case 2:
        Position = "third";
        break;
    case 3:
        Position = "fourth";
        break;
    case 4:
        Position = "fifth";
        break;
    case 5:
        Position = "sixth";
        break;
    case 6:
        Position = "seventh";
        break;
    case 7:
        Position = "eighth";
        break;
    case 8:
        Position = "ninth";
        break;
    default:
        TArray<FStringFormatArg> FormatArgs;
        FormatArgs.Add(FStringFormatArg(Index));
        Position = FString::Format(TEXT("{0}th"), FormatArgs);
    }
    PrintLine(TEXT("Here's a hint: the %s character is %c"), *Position, HiddenWord[Index]);
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count = {0, 0};
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}