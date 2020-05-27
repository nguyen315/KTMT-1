#include "Constants.h"
#include "QInt.h"
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	//// Test phần input và output
	//// Sửa maxlength trong constant thành 8 bit cho dễ test ## 2^7 = 128
	//QInt* a;
	//a = new QInt(2, "11111110");
	//cout << a->getBinaryType() << endl;
	////cout << a->getDecimalType() << endl;
	//cout << a->getHexaType() << endl;
	//delete a;
	//a = new QInt(10, "-120");
	//cout << a->getBinaryType() << endl;
	//cout << a->getHexaType() << endl;
	///*cout << a->getDecimalType() << endl;*/
	//delete a;
	//a = new QInt(16, "7F");
	//cout << a->getBinaryType() << endl;
	//cout << a->getDecimalType() << endl;
	//delete a;
	QInt aa(2, "10111");
	QInt b(2, "111");
	QInt c(2, "1011");
	aa = b + c;
	cout << aa.getBinaryType() << endl;
}