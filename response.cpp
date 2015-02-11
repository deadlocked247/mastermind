#include "response.h"
#include <iostream>
using namespace std;

//Constructor for response object
response::response()
{
	numCorrect = 0;
	numIncorrect = 0;
}

//Constructor for response object
response::response(int correct, int incorrect)
{
	numCorrect = correct;
	numIncorrect = incorrect;
}

//Returns the number of correct values
int response::getNumCorrect()
{
	return numCorrect;
}

//Returns the number of incorrect values
int response::getNumIncorrect()
{
	return numIncorrect;
}

//Sets the number of correct values to the passed in value
void response::setNumCorrect(int num)
{
	numCorrect = num;
}

//Sets the number of incorrect values to the passed in value
void response::setNumIncorrect(int num)
{
	numIncorrect = num;
}

//Operator for setting the value of response based on another response object
response &response::operator=(const response &rhs)
{
	numCorrect = rhs.numCorrect;
	numIncorrect = rhs.numIncorrect;
	return *this;
}

//Overloaded operator for comparing two response objects
bool operator==(const response &r1, const response &r2)
{
	return (r1.numCorrect == r2.numCorrect && r1.numIncorrect == r2.numIncorrect);
}

//Overloaded operator for printing response objects
ostream &operator<<(ostream &ostr, const response &r1)
{
	ostr << '(' << r1.numCorrect << ',' << r1.numIncorrect << ')';
	return ostr;
}
