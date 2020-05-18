#include "QInt.h"

QInt::QInt(int type, string number)
{
	if (type == 2) {
		arrBits = Number::inputBinary(number);
	}
	else if (type == 10) {
		arrBits = Number::inputDecimal(number);
	}
	else {
		arrBits = Number::inputHexa(number);
	}
}

string QInt::getBinaryType()
{
	string binaryString;
	for (int i = 0; i < arrBits.size(); i++) {
		if (arrBits[i]) binaryString.push_back('1');
		else binaryString.push_back('0');
	}
	return binaryString;
}

string QInt::getDecimalType()
{
	string decimalString;
	
	return decimalString;
}
