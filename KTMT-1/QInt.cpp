#include "QInt.h"
#include "Constants.h"

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

void QInt::operator>>(int x)
{
	if (x < 0)
		return;

	if (arrBits.size() >= Constants::maxLength)
	{
		if (x >= arrBits.size())
		{
			arrBits.clear();
			arrBits.push_back(0);
			return;
		}

		for (int i = arrBits.size() - 1; i >= x; i--)
			arrBits[i] = arrBits[i - x];

		for (int i = 0; i < x; i++)
			arrBits[i] = arrBits[0];
	}
	else
	{
		if (x >= arrBits.size())
		{
			arrBits.clear();
			arrBits.push_back(0);
			return;
		}

		for (int i = 0; i < x; i++)
			arrBits.pop_back();
	}
}

void QInt::operator<<(int x)
{
	if (x < 0)
		return;

	if (arrBits.size() >= Constants::maxLength)
	{
		for (int i = 0; i < x; i++)
		{
			arrBits.push_back(0);
			arrBits.erase(arrBits.begin());
		}

		Number::removeZeroPrefix(arrBits);
		return;
	}

	if (arrBits.size() + x > Constants::maxLength) {
		
		int overValue = arrBits.size() + x - Constants::maxLength;

		for (int i = 0; i < overValue; i++)
			arrBits.erase(arrBits.begin());

		for (int i = 0; i < x; i++)
			arrBits.push_back(0);

		Number::removeZeroPrefix(arrBits);
		return;
	}

	for (int i = 0; i < x; i++)
		arrBits.push_back(0);
}

void QInt::rol() {

	if (arrBits.size() < Constants::maxLength) {
		arrBits.push_back(false);
	}

	else if (arrBits.size() == Constants::maxLength) {
		vector<bool>::iterator head;
		head = arrBits.begin();
		bool bit_Rol = arrBits.at(0);
		arrBits.erase(head);
		arrBits.push_back(bit_Rol);
	}
	Number::removeZeroPrefix(arrBits);
}


void QInt::ror() {
	int n = arrBits.size();
	if (arrBits.size() < Constants::maxLength) {
		if (arrBits.back() == true) {
			for (int i = 0; i <= Constants::maxLength - n; i++) {
				arrBits.insert(arrBits.begin(), false);
			}
			arrBits.insert(arrBits.begin(), false);
		}
		arrBits.pop_back();
	}

	else if (arrBits.size() == Constants::maxLength) {
		bool bit_Ror = arrBits.at(arrBits.size() - 1);
		arrBits.insert(arrBits.begin(), bit_Ror);
		arrBits.pop_back();
	}
	Number::removeZeroPrefix(arrBits);
}