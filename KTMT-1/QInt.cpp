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

void QInt::rol(int x) {
	vector<bool>::iterator head;
	bool ele = arrBits.at(0);
	head = arrBits.begin();
	arrBits.erase(head);
	arrBits.push_back(ele);
}
void QInt::ror(int x) {
	vector<bool>::iterator tail;
	tail = arrBits.end();
	bool ele = arrBits.at(arrBits.size() - 1);
	arrBits.pop_back();
	arrBits.insert(tail, ele);
}