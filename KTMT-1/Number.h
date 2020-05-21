#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Constants.h"

using namespace std;

class Number
{
private:
	static string twoPowerX[128];
	static unordered_map<char, string> hexMap;
public:
	static vector<bool> inputBinary(string number);
	static vector<bool> inputDecimal(string number);
	static vector<bool> inputHexa(string number);
	static string div2(string number);
	static string mult2(string number);

	static string getTwoPowerX(int x);
	static string sum(string x, string y);
	// static string subtract(string x, string y); // bảo đảm x lúc nào cũng lớn hơn hoặc bằng y
	
	static unordered_map<char, string> initHexMap();
	static char getHexFromBinary(string bin);
	static void toTwoComplement(vector<bool>& arrBits);
};

#endif // !NUMBER_H