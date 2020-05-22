#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <string>

using namespace std;

class Number
{
public:
	static vector<bool> inputBinary(string number);
	static vector<bool> inputDecimal(string number);
	static vector<bool> inputHexa(string number);
	static string div2(string number);
	static void removeZeroPrefix(vector<bool>&);
};

#endif // !NUMBER_H