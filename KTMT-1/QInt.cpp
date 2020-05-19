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
	
	for (int i = arrBits.size() - 1; i >= 0; i--) {
		if (arrBits.size() - i == Constants::maxLength) break; // trường hợp có bit thứ 128 --> có thể là số âm
		if (arrBits[i]) {
			string temp = Number::getTwoPowerX(arrBits.size() - 1 - i);
			decimalString = Number::sum(decimalString, temp);
		}
	}
	if ((arrBits.size() == Constants::maxLength) && arrBits[0]) { // trường hợp số âm
		string temp = Number::getTwoPowerX(Constants::maxLength - 1);
		// Lấy số âm ở bit cao nhất này trừ cho kết quả trên
		decimalString = Number::subtract(temp, decimalString);
		// Đổi dấu lại thành dấu âm
		decimalString.insert(0, 1, '-');

	}
	return decimalString;

}

