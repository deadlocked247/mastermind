// Project 1b
// Alexander Hubicki
// Burak Aslan
#include <iostream>
#include <cstdlib>
#include "mastermind.h"
#include "d_except.h"
using namespace std;

//Inits a mastermind object and calls playGame()
void main()
{
	char input;
	cout << "Are you playing as the codebreaker? (Y/n)\t";
	cin >> input;
	try
	{
		if (input == 'Y' || input == 'y')
		{
			cout << "Input Valid" << endl << "Starting game as CODEBREAKER..." << endl;
			mastermind mastermindObj;
			mastermindObj.playGame();
			//mastermindObj.playGamedebug(); //used for debugging only
		}
		else if (input == 'N' || input == 'n')
		{
			cout << "Input Valid" << endl << "Starting game as CODEMAKER..." << endl;
			mastermind mastermindObj;
			mastermindObj.playGame2();
		}
		else
		{
			throw rangeError("Not a valid input"); //Throw range error to catch later
		}
	}

	catch (rangeError(&ex))
	{
		cout << "Range Error: " << ex.what() << endl;
	}

	system("pause");
}