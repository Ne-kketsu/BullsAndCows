#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry()  const { return (MyCurrentTry); }
int32 FBullCowGame::GetMaxTries() const { return (MyMaxTries); }
int32 FBullCowGame::GetHiddenWordLentgh() const{ return (MyHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return (bGameIsWon); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 10;
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return (EGuessStatus::Not_Isogram);
	}
	else if (!IsLowercase(Guess))
	{
		return (EGuessStatus::Not_Lowercase);
	}
	else if (Guess.length() != GetHiddenWordLentgh())
	{
		return (EGuessStatus::Wrong_Lentgh);
	}
	else
		return (EGuessStatus::OK);

	return (EGuessStatus::OK);
}

//receive a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	FBullCowCount Count;

	//loop through all letter in the guess n compare to hidden word
	for (int32 j = 0; j < MyHiddenWord.length(); j += 1) {
		for (int32 i = 0; i < Guess.length(); i += 1) {
			if (Guess[i] == MyHiddenWord[j] && i == j)
				Count.Bulls += 1;
			else if (Guess[i] == MyHiddenWord[j] && i != j)
				Count.Cows += 1;
		}
	}
	if (Count.Bulls == GetHiddenWordLentgh())
		bGameIsWon = true;
	else
		bGameIsWon = false;
	MyCurrentTry += 1;
	return (Count);
}

void FBullCowGame::PrintGameSummary() const
{
	if (IsGameWon())
		std::cout << "\nYOU WIN. Fantastic. \n";
	else
		std::cout << "\nYOU LOST. The Hidden word was ~> " << MyHiddenWord << " \n";
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap <char, bool> LetterSeen;

	if (Guess.length() <= 1)
		return (true);
	for (auto Letter : Guess) { //For all letters of the word
		Letter = tolower(Letter); //Handle mixed case
		if (LetterSeen[Letter])
			return (false);
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return (true);
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() < 1)
		return (false);
	for (char Letter : Guess) {
		if (!islower(Letter))
			return (false);
	}
	return (true);
}

void FBullCowGame::GetHint() const
{
	return;
}