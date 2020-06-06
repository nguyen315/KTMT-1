#include "QInt.h"
#include "Constants.h"
#include<iostream>

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

		if (arrBits[i])
			binaryString.push_back('1');

		else
			binaryString.push_back('0');
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


QInt QInt::operator + (QInt& other) {
	int l1 = this->arrBits.size();
	int l2 = other.arrBits.size();
	QInt result(2, "");
	bool storeBit = 0;
	int longer = 0;

	// = 1 khi cả 2 đều dương
	bool bothPositive = (!Number::getSignOfNumber(this->arrBits)) & (!Number::getSignOfNumber(other.arrBits));

	// = 1 khi cả 2 đều âm
	bool bothNegative = Number::getSignOfNumber(this->arrBits) & Number::getSignOfNumber(other.arrBits);

	// = 1 khi khác dấu
	bool different = Number::getSignOfNumber(this->arrBits) ^ Number::getSignOfNumber(other.arrBits);

	/*làm cho hai số bằng nhau sau đó thêm một bit 0 vào đầu hai số

	Nếu cả 2 đều âm thì nếu bit một bằng 0 thì là overflow
	Nếu cả 2 đều dương thì chạm vào bit 1 thì throw
	Nếu khác dấu thì không throw vì input bảo đảm đúng thì số âm + số dương k bao giờ overflow*/
	if (l1 > l2) {
		longer = l1;
		for (int i = l2; i <= l1; i++) {
			other.arrBits.insert(other.arrBits.begin(), false);
		}
		arrBits.insert(arrBits.begin(), false);
	}
	else if (l1 < l2) {
		longer = l2;
		for (int i = l1; i <= l2; i++) {
			arrBits.insert(arrBits.begin(), false);
		}
		other.arrBits.insert(other.arrBits.begin(), false);
	}
	else {
		longer = l1;
		arrBits.insert(arrBits.begin(), false);
		other.arrBits.insert(other.arrBits.begin(), false);
	}

	result.arrBits.resize(longer + 1);


	for (int i = longer; i >= 0; i--) {

		// Trường hợp overflow
		if (i == 0) {
			if (bothPositive) {
				if (longer == Constants::maxLength - 1 && storeBit) {
					throw 0;
				}
			}

			else if (bothNegative) {
				if (longer == Constants::maxLength && result.arrBits[1] == 0) {
					throw 0;
				}
			}

			result.arrBits[0] = storeBit;
		}

		else {
			// both 0
			if (arrBits[i] == 0 && other.arrBits[i] == 0) {
				if (storeBit == 0) {
					result.arrBits[i] = 0;
				}
				else {
					result.arrBits[i] = 1;
					storeBit = 0;
				}
			}
			// both 1
			else if (arrBits[i] == 1 && other.arrBits[i] == 1) {
				if (storeBit == 1) {
					result.arrBits[i] = 1;
				}
				else {
					result.arrBits[i] = 0;
				}
				storeBit = 1;
			}
			// diffirent
			else {
				if (storeBit == 1) {
					result.arrBits[i] = 0;
					storeBit = 1;
				}
				else {
					result.arrBits[i] = 1;
				}
			}
		}

	}

	if (different || bothNegative) {
		result.arrBits.erase(result.arrBits.begin());
	}

	Number::removeZeroPrefix(result.arrBits);
	return result;


}


QInt QInt::operator - (QInt& other) {
	QInt reverse(2, "");
	reverse = other;
	Number::toTwoComplement(reverse.arrBits);
	return *this + reverse;
}


QInt& QInt::operator=(const QInt& other)
{
	arrBits = other.arrBits;
	return *this;
}

QInt QInt::operator&(QInt& other)
{
	string _arrBits = "";

	// AND từng bit cho đến khi một trong 2 hết bit thì dừng lại, vì lúc đó bit nào còn lại & với 0 cũng bằng 0
	for (int i = this->arrBits.size() - 1, j = other.arrBits.size() - 1; i >= 0 && j >= 0; i--, j--) {
		_arrBits.insert(0, to_string((this->arrBits[i] & other.arrBits[j])));
	}


	QInt result(2, _arrBits);


	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return result;
}

QInt QInt::operator|(QInt& other)
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

	QInt result(2, _arrBits);

	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return result;
}

QInt QInt::operator^(QInt& other)
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

	QInt result(2, _arrBits);

	// Trong hàm tạo đã xử lý các số 0 ở đầu
	return result;
}

QInt& QInt::operator~()
{
	while (arrBits.size() < Constants::maxLength) {
		arrBits.insert(arrBits.begin(), 0);
	}
	for (int i = 0; i < this->arrBits.size(); i++) {
		this->arrBits[i] = !this->arrBits[i];
	}

	// Xử lý số 0 ở đầu
	Number::removeZeroPrefix(this->arrBits);
	return *this;
}

QInt QInt::operator*(QInt& other)
{
	vector<bool> firstArr = arrBits;
	vector<bool> secondArr = other.arrBits;

	if (Number::getSignOfNumber(arrBits) == 1)
		Number::toTwoComplement(firstArr);

	if (Number::getSignOfNumber(secondArr) == 1)
		Number::toTwoComplement(secondArr);


	QInt temp(2, "0");
	QInt sum(2, "0");

	for (int i = firstArr.size() - 1; i >= 0; i--)
	{
		if (firstArr[i])
			temp.arrBits = secondArr;
		else continue;

		temp << firstArr.size() - 1 - i;

		if (temp.arrBits.size() == Constants::maxLength) {

			// Nếu 2 số khác dấu thì có thể đụng tới bit cao nhất 
			if (Number::getSignOfNumber(arrBits) ^ Number::getSignOfNumber(other.arrBits)) {
				QInt c(2, "0");
				try {
					c = sum + temp;
					Number::removeZeroPrefix(c.arrBits);
				}
				catch (int e) {
					throw e;
				}

				// thiết đặt số QInt min
				QInt min(2, "0");
				while (min.arrBits.size() < Constants::maxLength)
					min.arrBits.push_back(0);
				min.arrBits[0] = 1;

				// đụng tới bit cao nhất, nếu không phải là QInt min hoặc không phải vòng lặp cuối cùng thì throw
				if (c.arrBits == min.arrBits && i == 0) {
					return c;
				}
				else
					throw 0;
			}

			else
				throw 0;
		}



		try
		{
			sum = sum + temp;
		}
		catch (int e)
		{
			throw e;
		}
	}

	if (Number::getSignOfNumber(arrBits) ^ Number::getSignOfNumber(other.arrBits))
	{
		Number::toTwoComplement(sum.arrBits);
	}

	Number::removeZeroPrefix(sum.arrBits);

	return sum;
}

QInt QInt::operator/(QInt& other)
{
	QInt Quotient(2, "");
	QInt Remainder(2, "");

	vector<bool> devidend = arrBits;
	vector<bool> devisor = other.arrBits;

	if (Number::getSignOfNumber(devidend) == 1)
		Number::toTwoComplement(devidend);

	if (Number::getSignOfNumber(devisor) == 1)
		Number::toTwoComplement(devisor);

	for (int i = 0; i < devidend.size(); i++)
	{
		Remainder.arrBits.push_back(devidend[i]);

		if (Remainder < other)
		{
			Quotient.arrBits.push_back(0);
		}
		else
		{
			Quotient.arrBits.push_back(1);
			Remainder = Remainder - other;
		}
	}

	if (Number::getSignOfNumber(arrBits) ^ Number::getSignOfNumber(other.arrBits))
	{
		Number::toTwoComplement(Quotient.arrBits);
	}

	Number::removeZeroPrefix(Quotient.arrBits);

	return Quotient;


}

bool QInt::operator>(QInt& other)
{
	Number::removeZeroPrefix(this->arrBits);
	Number::removeZeroPrefix(other.arrBits);
	if (arrBits.size() > other.arrBits.size())
		return true;
	else if (arrBits.size() == other.arrBits.size())
	{
		return getBinaryType().compare(other.getBinaryType()) > 0;
	}

	return false;
}

bool QInt::operator<(QInt& other)
{
	Number::removeZeroPrefix(this->arrBits);
	Number::removeZeroPrefix(other.arrBits);
	if (arrBits.size() < other.arrBits.size())
		return true;
	else if (arrBits.size() == other.arrBits.size())
	{
		return getBinaryType().compare(other.getBinaryType()) < 0;
	}

	return false;
}