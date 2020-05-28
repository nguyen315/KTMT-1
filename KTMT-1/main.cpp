#include "Constants.h"
#include "QInt.h"
#include <iostream>
#include "OverflowException.h"

using namespace std;

int main() {
	// Test phần input và output
	// Sửa maxlength trong constant thành 8 bit cho dễ test ## 2^7 = 128
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



	/*int x = 8;
	int y = 9;

	cout << (x | y) << endl;*/

	QInt* a, * b;
	a = new QInt(2, "10110001");
	b = new QInt(2, "11001");
	QInt* c;

	c = &(*a & *b);
	cout << "&: " << c->getBinaryType() << endl;
	delete c;

	c = &(*a | *b);
	cout << "|: " << c->getBinaryType() << endl;
	delete c;

	c = &(*a ^ *b);
	cout << "^: " << c->getBinaryType() << endl;
	delete c;

	c = &(~*a);
	cout << "~: " << c->getBinaryType() << endl;
	delete c;

	QInt* a = new QInt(2, "111");
	QInt* b = new QInt(2, "010");
	QInt* c = new QInt(2, "");

	try
	{
		*c = *a * *b;
	}
	catch (int e)
	{
		cerr << "0" << endl;
	}
	cout << a->getBinaryType() << endl;

}