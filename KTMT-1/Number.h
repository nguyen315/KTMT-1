#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <string>
#include <bitset>
#include "Constants.h"

using namespace std;

class Number
{
private:
	static string twoPowerX[128];
public:
	static vector<bool> inputBinary(string number);
	static vector<bool> inputDecimal(string number);
	static vector<bool> inputHexa(string number);
	static string div2(string number);
	static string mult2(string number);

	static string getTwoPowerX(int x);
	static string sum(string x, string y);
	static string subtract(string x, string y); // bảo đảm x lúc nào cũng lớn hơn hoặc bằng y
};

#endif // !NUMBER_H