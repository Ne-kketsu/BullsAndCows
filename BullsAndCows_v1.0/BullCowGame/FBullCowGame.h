#pragma once
#include <iostream>
#include <string>

using int32 = int;
using FString = std::string;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Alphanum,
	Wrong_Lentgh,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLentgh() const;
	bool IsGameWon() const;
	void GetHint() const;
	void PrintGameSummary() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset();
	FBullCowCount SubmitGuess(FString);
private:
	//See constructor for initialize
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};