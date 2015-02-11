#include <iostream>
#include <vector>
#include "mastermind.h"
#include "d_except.h"
#include <algorithm> 
using namespace std;

//Constructor for mastermind class
mastermind::mastermind()
{
}

//Prints the secret code to the screen
void mastermind::printSecretCode()
{
	cout << "\nSecret Code:\t\n";
	cout << secretCode;
}

//Creates and returns the player's guess
code mastermind::humanGuess()
{
	int guess[4];
	int x, i;

	cout << "\nPlease enter your guess ( integer range [0,5] ):\n";
	for (i = 0; i < 4; i++)
	{
		cout << "Position " << i+1 << ":\t";
		cin >> x;
		if ((cin.fail()) || (x > 5) || (x < 0))
		{
			throw rangeError("Not a valid input for guess"); //Throw range error to catch later
		}
		else
		{
			guess[i] = x;
		}
	}

	code guessCode(guess[0], guess[1], guess[2], guess[3]);
	cout << "\nYou guessed:\t";
	cout << guessCode;

	return guessCode;
}

//Checks whether the guess is consistent with previous guesses
bool mastermind::consistentWithPreviousGuesses(code guess)
{
	int size = previousResponse.size();
	int k, j;
	int i = 0;
	if (size == 0)
	{
		return true;
	}
	do {
		j = guess.checkCorrect(previousCode[i]);
		k = guess.checkIncorrect(previousCode[i]);
		response r(j, k);
		if (!(r == previousResponse[0]))
		{
			return false;
		}
		i++;
	} while (i != size);

	return true;
}

//Creates and returns the commputer's guess
code mastermind::agentGuess()
{
	code base(0, 0, 0, 0);
	code checkGuess(0, 0, 0, 0);
	code checkGuess2(0, 0, 0, 0);
	code bestGuess;
	int ans[2] = { 4, 0 };
	int correct, incorrect;
	int currentScore = 0;
	int bestScore = 1296;
	int responseCases[13][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 3, 0 } };

	do {

		for (int i = 0; i < 14; i++)
		{
			response r(responseCases[i][0], responseCases[i][1]);
			previousResponse.push_back(r);
			previousCode.push_back(checkGuess);

			do
			{
				if (consistentWithPreviousGuesses(checkGuess2))
				{
					currentScore++;
				}
				checkGuess2 = checkGuess2.increment();
			} while (!(checkGuess2.areCodesEqual(base)));

			previousResponse.pop_back();
			previousCode.pop_back();
		}

		if (currentScore <= bestScore)
		{
			code bestGuess(checkGuess.getCode(3), checkGuess.getCode(2), checkGuess.getCode(1), checkGuess.getCode(0));
			bestScore = currentScore;
		}

		checkGuess = checkGuess.increment();
		currentScore = 0;
	} while (!checkGuess.areCodesEqual(base));

	return bestGuess;
}

//Used for debugging purposes so that the secret code is visible
void mastermind::playGamedebug()
{
	bool isGameOver = false; //exits the game loop when true
	int guessCounter = 0; //counts the number of guesses made
	cout << "SECRET CODE IS: " << secretCode << endl;
	do {
		//ends the game loop when 10 guesses have been made
		if (guessCounter == 10)
		{
			cout << "\nThe computer is out of guesses. You win!\n";
			printSecretCode();
			isGameOver = true;
		}

		code guess = agentGuess();
		response res = getResponse(guess);

		if (isSolved(res))
		{
			printSecretCode();
			cout << "\n\n\n---- The computer wins! You lose... ----\n";
			isGameOver = true;
		}
		else
		{
			previousResponse.push_back(res);
			previousCode.push_back(guess);
			guessCounter++;
		}
	} while (isGameOver == false);
}

//Inputs: the secret code and the guess code
//Return: a response object created using the guess code
response mastermind::getResponse(code guess)
{
	int correct = secretCode.checkCorrect(guess);
	int incorrect = secretCode.checkIncorrect(guess);

	response response(correct, incorrect);
	return response;
}

//Determines if the code has been guessed
//Return: true if all numbers in the guess are correct
bool mastermind::isSolved(response res)
{
	return (res.getNumCorrect() == 4);
}

//Main game loop for when the player is the codebreaker
void mastermind::playGame()
{
	bool isGameOver = false; //exits the game loop when true
	bool isGuessed = false; //prevents a repeated guess from being counted by the guess counter
	int guessCounter = 0; //counts the number of guesses made

	do {
		//ends the game loop when 10 guesses have been made
		if (guessCounter == 10)
		{
			cout << "\nYou are out of guesses! You lose.\n";
			printSecretCode();
			isGameOver = true;
		}

		code guess = humanGuess();
		response res = getResponse(guess);

		if (isSolved(res))
		{
			printSecretCode();
			cout << "\n\n\n---- You win! ----\n";
			isGameOver = true;
		}
		else
		{
			//checks the vector list of responses to see if the guess has already been made
			for (int i = 0; i < previousCode.size(); i++)
			{
				if (previousCode[i].areCodesEqual(guess))
				{
					isGuessed = true;
				}
			}

			previousCode.push_back(guess); //puts the value at the end of the vector

			if (isGuessed == false)
			{
				cout << "\nThe response is:\t" << "(" << res.getNumCorrect() << "," << res.getNumIncorrect() << ")\n";
				guessCounter++;
			}
			else
			{
				cout << "\nYou already guessed that! Try again.\n";
				isGuessed = false;
			}

			cout << "Guesses left:\t" << 10 - guessCounter << "\n\n";
		}
	} while (isGameOver == false);
}

//Main game loop for when the player is the codemaker
void mastermind::playGame2()
{
	bool isGameOver = false; //exits the game loop when true
	int guessCounter = 0; //counts the number of guesses made

	int newCode[4];
	cout << "\nPlease create your secret code:\n";
	cout << "Position 1:\t";
	cin >> newCode[0];
	cout << "Position 2:\t";
	cin >> newCode[1];
	cout << "Position 3:\t";
	cin >> newCode[2];
	cout << "Position 4:\t";
	cin >> newCode[3];
	secretCode.setCode(newCode); //creates the player's secret code

	do {
		//ends the game loop when 10 guesses have been made
		if (guessCounter == 10)
		{
			cout << "\nThe computer is out of guesses. You win!\n";
			printSecretCode();
			isGameOver = true;
		}

		code guess = agentGuess();
		response res = getResponse(guess);

		if (isSolved(res))
		{
			printSecretCode();
			cout << "\n\n\n---- The computer wins! You lose... ----\n";
			isGameOver = true;
		}
	} while (isGameOver == false);
}

//overloaded operator for printing the secret code
ostream &operator<<(ostream &output, const mastermind &m)
{
	output << m.secretCode;
	return output;
}