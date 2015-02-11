#include "code.h"
#include "response.h"

class mastermind
{
public:
	mastermind();
	void printSecretCode();
	code humanGuess();
	code agentGuess();
	bool consistentWithPreviousGuesses(code);
	response getResponse(code);
	bool isSolved(response);
	void playGame();
	void playGame2();
	void playGamedebug();
	friend ostream &operator<<(ostream &output, const mastermind &m);
private:
	code secretCode;
	vector<code> previousCode;
	vector<response> previousResponse;
};
