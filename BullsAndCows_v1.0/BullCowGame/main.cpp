/* This is the console executable, that makes usse of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/

#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;
void print_intro(void);
void PlayGame(void);
FText GetValidGuess(void);
bool PlayAgain(void);
FBullCowGame BCGame;

int main(void)
{
	print_intro();
	do {
		PlayGame();
	} while (PlayAgain());
	return (0);
}

void print_intro(void)
{
	//introduce the game
	int32 HWLentgh = BCGame.GetHiddenWordLentgh();
	std::cout << "Hey I'm finally starting my personal project.\n" << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "So, can you guess the " << HWLentgh;
	std::cout << " letter isogram I'm thinking of ?\n\n";
}

void PlayGame(void)
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";
	FBullCowCount Count;

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
			Guess = GetValidGuess();

			Count = BCGame.SubmitGuess(Guess);
			std::cout << "Bulls = " << Count.Bulls << " | Cows = " << Count.Cows << '\n';
	}
	BCGame.PrintGameSummary();
}


FText GetValidGuess(void)
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ".\n";

	do {
		//get a guess from the player
		std::cout << "Enter your guess : ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid Isogram (=Word without repeating letters)\n";
			break;
		case EGuessStatus::Wrong_Lentgh:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLentgh() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase isogram\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return (Guess);
}

bool PlayAgain(void)
{
	FText Answer = "";

	std::cout << "Play again ?" << '\n' << "y/n: ";
	std::getline(std::cin, Answer);
	while (1) {
		if (Answer == "y" || Answer == "Y")
			return (true);
		else if (Answer == "n" || Answer == "N")
			return (false);
		else {
			std::cout << "Please enter valid answer.\n";
			std::cout << "y/n OR Y/N: ";
			std::getline(std::cin, Answer);
		}
	}
}
