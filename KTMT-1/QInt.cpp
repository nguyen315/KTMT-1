#include "QInt.h"
#include "Constants.h"
#include<iostream>
using namespace std;
int flagMinus = 0;

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
	string result;
	bool isNegative = false;
	// Trường hợp là số 0
	if (arrBits.size() == 1 && arrBits[0] == 0) {
		result = "0";
		return result;
	}

	// Nếu là số âm thì lấy bù 2 lại để thành số dương
	if (arrBits.size() == Constants::maxLength && arrBits[0]) {
		isNegative = true;
		Number::toTwoComplement(arrBits);
	}
	// Đưa số dương tương ứng vào result
	for (int i = arrBits.size() - 1; i >= 0; i--) {
		if (arrBits[i]) {
			string temp = Number::getTwoPowerX(arrBits.size() - 1 - i);
			result = Number::sum(result, temp);
		}
	}

	// Nếu là số âm thì thêm dấu trừ phía trước
	if (isNegative)
		result.insert(0, 1, '-');

	return result;
}

string QInt::getHexaType() {
	string result, bin;
	bool isNegative = false;
	char hex;

	// Nếu là số âm thì lấy bù 2 lại để thành số dương
	if ((arrBits.size() == Constants::maxLength) && arrBits[0]) {
		isNegative = true;
		Number::toTwoComplement(arrBits);
	}

	// Đưa số dương vào result
	int i = arrBits.size() - 1;
	while (i >= 0) {
		bin.insert(0, to_string(arrBits[i]));

		// Nếu đủ 4 bit thì bắt đầu tìm mã hex rồi insert vào result
		if (bin.length() == 4) {
			hex = Number::getHexFromBinary(bin);
			result.insert(0, 1, hex);

			// Làm sạch string bin sẵn sàng cho lần nạp bit tiếp theo
			bin.clear();
		}
		i--;
	}

	// Trường hợp hết arrBits rồi nhưng bin vẫn đang chứa kí tự
	if (bin.length() != 0) {
		// insert thêm 0 vào đầu cho đủ 4 bit
		while (bin.length() < 4) {
			bin.insert(0, 1, '0');
		}
		hex = Number::getHexFromBinary(bin);
		result.insert(0, 1, hex);
	}

	// Nếu là số âm thì insert thêm dấu -
	if (isNegative)
		result.insert(0, 1, '-');

	return result;
}


void QInt::operator>>(int x)
{
	if (x < 0)
		return;

	if (arrBits.size() >= Constants::maxLength)
	{
		if (x >= arrBits.size())
		{
			// Tạo vector foo với maxLength số 1
			vector<bool> foo(Constants::maxLength, 1);

			// gán arrBits = foo
			arrBits = foo;
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



QInt& QInt::operator + (QInt& other) {
	int l1 = this->arrBits.size();
	int l2 = other.arrBits.size();
	QInt* result = new QInt(2, "");
	bool storeBit = 0;
	int longer = 0;
	if (l1 > l2) {
		longer = l1;
		for (int i = l2; i <= l1; i++) {
			if(flagMinus == 0) other.arrBits.insert(other.arrBits.begin(), false);
			else other.arrBits.insert(other.arrBits.begin(), true);
		}
		if (flagMinus == 0) arrBits.insert(arrBits.begin(), false);
		else arrBits.insert(arrBits.begin(), true);
	}
	else if(l1 < l2) {
		longer = l2;
		for (int i = l1; i <= l2; i++) {
			arrBits.insert(arrBits.begin(), false);
		}
		other.arrBits.insert(other.arrBits.begin(), false);
	}
	else {
		longer = l1;
		if (flagMinus == 0) {
			arrBits.insert(arrBits.begin(), false);
			other.arrBits.insert(other.arrBits.begin(), false);
		}
		else {
			arrBits.insert(arrBits.begin(), true);
			other.arrBits.insert(other.arrBits.begin(), true);
		}
	}
	cout << this->getBinaryType() << endl;
	cout << other.getBinaryType() << endl;
	result->arrBits.resize(longer + 1);
	for (int i = longer; i >= 0; i--) {
		// both 0
		if (arrBits[i] == 0 && other.arrBits[i] == 0) {
			if (storeBit == 0) {
				result->arrBits[i] = 0;
			}
			else {
				result->arrBits[i] = 1;
				storeBit = 0;
			}
		}
		// both 1
		else if (arrBits[i] == 1 && other.arrBits[i] == 1) {
			if (storeBit == 1) {
				result->arrBits[i] = 1;
			}
			else {
				result->arrBits[i] = 0;
			}
			storeBit = 1;
		}
		// diffirent
		else {
			if (storeBit == 1) {
				result->arrBits[i] = 0;
				storeBit = 1;
			}
			else {
				result->arrBits[i] = 1;
			}
		}
		if (i == 0) {
			if (longer == 128 && storeBit == 1) {
				throw 0;
			}
			result->arrBits[0] = result->arrBits[0] + storeBit;
		}
	}
	if(flagMinus == 1 && result->arrBits[0] == 1) result->arrBits[0] = 0;
	Number::removeZeroPrefix(result->arrBits);
	flagMinus = 0;
	return *result;
}


QInt& QInt::operator - (QInt& other) {
	QInt* reverse = new QInt(2, "");
	reverse->arrBits = other.arrBits;
	for (int i = reverse->arrBits.size() - 1; i >= 0; i--) {
		if (reverse->arrBits[i] == 1) {
			for (int j = 0; j < i; j++) {
				reverse->arrBits[j] = !reverse->arrBits[j];
			}
			break;
		}
	}
	flagMinus = 1;
	return *this + *reverse;
}


QInt& QInt::operator=(const QInt& other)
{
	arrBits = other.arrBits;
	return *this;
}