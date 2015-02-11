#include <vector>
using namespace std;

class code
{
public:
	code();
	code(int,int,int,int);
	void setCode(int[]);
	void generateCode();
	int checkCorrect(code);
	int checkIncorrect(code);
	bool areCodesEqual(code);
	int getCode(int);
	code increment();
	friend ostream &operator<<(ostream &output, const vector<int> &vector);
	friend ostream &operator<<(ostream &output, const code &c);
private:
	vector<int> codeVector;
};
