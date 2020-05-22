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

	static string mult2(string number);

	static string getTwoPowerX(int x);
	static string sum(string x, string y);
	
	static unordered_map<char, string> initHexMap();
	static char getHexFromBinary(string bin);
	static void toTwoComplement(vector<bool>& arrBits);

	static void removeZeroPrefix(vector<bool>&);

};

#endif // !NUMBER_H