// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    } else {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    /* Welcome Screen */
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));

    HiddenWord = Words[rand() % Words.Num()];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("The word is made of %i letters!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i tries!"), Lives);
    PrintLine(TEXT("Press Return to start playing!"));
    PrintLine(TEXT("The HiddenWord is: %s, length of %i!"), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (HiddenWord == Guess) 
    {
        EndGame();
        return;
    } 

    if(IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
    }

    --Lives;
    PrintLine(TEXT("Wrong! You\'ve still got %i tries left!"), Lives);
    if (!Lives) 
    {
        EndGame();
        return;
    } 

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("Your word must be %i letters long!"), HiddenWord.Len());
        return;
    }

    
}

void UBullCowCartridge::EndGame()
{
    if (!Lives)
    {
        PrintLine(TEXT("You\'ve lost!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
    }
    else
    {
        PrintLine(TEXT("You\'ve won!"));
    }
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return true;
            }
        }
    }
    return false;
}