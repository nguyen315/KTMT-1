﻿#include "QInt.h"
#include "Constants.h"
#include <iostream>
#include "OverflowException.h"
using namespace std;

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
	string binaryString = "";
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


QInt& QInt::operator&(QInt& other)
{
	string _arrBits = "";

	// AND từng bit cho đến khi một trong 2 hết bit thì dừng lại, vì lúc đó bit nào còn lại & với 0 cũng bằng 0
	for (int i = this->arrBits.size() - 1, j = other.arrBits.size() - 1; i >= 0 && j >= 0; i--, j--) {
		_arrBits.insert(0, to_string((this->arrBits[i] & other.arrBits[j])));
	}


	QInt *result = new QInt(2, _arrBits);


	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return *result;
}

QInt& QInt::operator|(QInt& other)
{
	string _arrBits = "";

	for (int i = this->arrBits.size() - 1, j = other.arrBits.size() - 1; i >= 0 && j >= 0; i--, j--) {
		_arrBits.insert(0, to_string((this->arrBits[i] | other.arrBits[j])));
	}

	// Tới đây có 2 TH, this->arrBits dài hơn hoặc other.arrBits dài hơn
	if (this->arrBits.size() > other.arrBits.size()) {
		for (int i = this->arrBits.size() - other.arrBits.size() - 1; i >= 0; i--) {
			_arrBits.insert(0, to_string(this->arrBits[i]));
		}
	}
	else {
		for (int i = other.arrBits.size() - this->arrBits.size() - 1; i >= 0; i--) {
			_arrBits.insert(0, to_string(other.arrBits[i]));
		}
	}

	QInt* result = new QInt(2, _arrBits);

	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return *result;
}

QInt& QInt::operator^(QInt& other)
{
	string _arrBits = "";

	for (int i = this->arrBits.size() - 1, j = other.arrBits.size() - 1; i >= 0 && j >= 0; i--, j--) {
		_arrBits.insert(0, to_string((this->arrBits[i] ^ other.arrBits[j])));
	}

	// Tới đây có 2 TH, this->arrBits dài hơn hoặc other.arrBits dài hơn
	if (this->arrBits.size() > other.arrBits.size()) {
		for (int i = this->arrBits.size() - other.arrBits.size() - 1; i >= 0; i--) {
			_arrBits.insert(0, to_string(this->arrBits[i] ^ 0));
		}
	}
	else {
		for (int i = other.arrBits.size() - this->arrBits.size() - 1; i >= 0; i--) {
			_arrBits.insert(0, to_string(other.arrBits[i] ^ 0));
		}
	}

	QInt* result = new QInt(2, _arrBits);

	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return *result;
}

QInt& QInt::operator~()
{
	for (int i = 0; i < this->arrBits.size(); i++) {
		this->arrBits[i] = !this->arrBits[i];
	}

	// Xử lý số 0 ở đầu
	Number::removeZeroPrefix(this->arrBits);
	return *this;
}

QInt& QInt::operator=(QInt& other)
{
	this->arrBits = other.arrBits;
=======
QInt& QInt::operator+(QInt& other) 
{
	// .....
	throw 0;
}

QInt& QInt::operator*(QInt& other) 
{
	QInt* temp = new QInt(2, "");
	QInt* sum = new QInt(2, "");

	for (int i = arrBits.size() - 1; i >= 0; i--)
	{
		if (arrBits[i])
			temp->arrBits = other.arrBits;
		else continue;

		*temp << arrBits.size() - 1 - i;

		try
		{
			*sum = *sum + *temp;
		}
		catch (int e)
		{
			throw e;
		}
	}

	delete temp;

	return *sum;
}

QInt& QInt::operator=(const QInt& other)
{
	// TODO: insert return statement here
	arrBits = other.arrBits;

	return *this;
}

