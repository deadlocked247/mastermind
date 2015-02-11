#include <vector>
using namespace std;

class response
{
public:
	response();
	response(int,int);
	int getNumCorrect();
	int getNumIncorrect();
	void setNumCorrect(int);
	void setNumIncorrect(int);
	response &operator=(const response &response);
	friend bool operator==(const response &r1, const response &r2);
	friend ostream &operator<<(ostream &ostr, const response &r1);
private:
	int numCorrect;
	int numIncorrect;
};