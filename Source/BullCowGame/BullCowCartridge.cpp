// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to bulls and cows!"));
    PrintLine(TEXT("Type something and press enter..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("hockey");
    PrintLine(Input);
}

/*

start game
set hidden word
prompt for guess
is guess correct?
if yes
    yay!
else
    boo.

*/