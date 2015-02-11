#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "code.h"
#include "response.h"
using namespace std;

//Constructor for code class that generates a random secret code
code::code()
{
	generateCode();
}

//Constructor for code class that creates a code from a guess
code::code(int pos1, int pos2, int pos3, int pos4)
{
	int codeArr[] = { pos1, pos2, pos3, pos4 };
	codeVector.insert(codeVector.begin(), codeArr, codeArr + 4);
}

//Sets the code objcet to the passed in the values
void code::setCode(int codeArr[])
{
	codeVector.clear();
	codeVector.insert(codeVector.begin(), codeArr, codeArr + 4);
}

//Inits the secret code randomly
void code::generateCode()
{
	int codeArr[4];
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		codeArr[i] = rand() % 6 + 1;
	}
	codeVector.assign(codeArr, codeArr + 4);
}

//Input: passed the guess as a parameter
//Return: the number of correct digits in the correct location
int code::checkCorrect(code guess)
{
	int numCorrect = 0;
	for (int i = 0; i < codeVector.size(); i++)
	{
		if (codeVector[i] == guess.codeVector[i])
		{
			numCorrect++;
		}
	}
	return numCorrect;
}

//Input: passed the guess as a parameter
//Return: the number of correct digits in the incorrect location
int code::checkIncorrect(code guess)
{	
	vector<int> codeTemp = codeVector;
	vector<int> temp; //temporary vector to store the values that are correct

	for (int i = 0; i < codeTemp.size(); i++)
	{
		if (codeTemp[i] == guess.codeVector[i])
		{
			codeTemp[i] = 7;
			guess.codeVector[i] = 7;
		}
	}

	for (int i = 0; i < codeTemp.size(); i++)
	{
		//if codeVector contains the value from the guess code and the values are not in the same position
		if (find(codeTemp.begin(), codeTemp.end(), guess.codeVector[i]) != codeTemp.end() && codeTemp[i] != guess.codeVector[i])
		{
			//if temp does not contain the value
			if (!(find(temp.begin(), temp.end(), guess.codeVector[i]) != temp.end()))
			{
				temp.push_back(guess.codeVector[i]);
			}
		}
	}
	return temp.size();
}

//Returns true if the current guess is equal to a previous guess
bool code::areCodesEqual(code guess)
{
	int sameValue = 0;

	for (int i = 0; i < codeVector.size(); i++)
	{
		if (codeVector[i] == guess.codeVector[i])
		{
			sameValue++;
		}
	}
	return (sameValue == 4);
}

//Increments the codeVector and returns the new code; used for CPU guessing
code code::increment()
{
	if (codeVector[3] != 5)
	{
		code c(codeVector[0], codeVector[1], codeVector[2], codeVector[3] + 1);
		return c;
	}
	else if (codeVector[3] == 5)
	{
		code c(codeVector[0], codeVector[1], codeVector[2] + 1, 0);
		return c;
	}
	else if (codeVector[2] != 5)
	{
		code c(codeVector[3], codeVector[2], codeVector[1] + 1, codeVector[0]);
		return c;
	}
	else if (codeVector[2] == 5)
	{
		code c(codeVector[3], codeVector[2] + 1, 0, 0);
		return c;
	}
	else if (codeVector[1] != 5)
	{
		code c(codeVector[3], codeVector[2] + 1, codeVector[1], codeVector[0]);
		return c;
	}
	else if (codeVector[1] == 5)
	{
		code c(codeVector[3] + 1, 0, 0, 0);
		return c;
	}
	else
	{
		code c(0, 0, 0, 0);
		return c;
	}
}

//Returns the codeVector at the specified index
int code::getCode(int i)
{
	return codeVector[i];
}

//Overloaded operator to print a vector of ints
ostream &operator<<(ostream &output, const vector<int> &vector)
{
	output << '(' << vector[0] << ',' << vector[1] << ',' << vector[2] << ',' << vector[3] << ')';
	return output;
}

//Overloaded operator to print a code object
ostream &operator<<(ostream &output, const code &c)
{
	output << '(' << c.codeVector[0] << ',' << c.codeVector[1] << ',' << c.codeVector[2] << ',' << c.codeVector[3] << ')';
	return output;
}