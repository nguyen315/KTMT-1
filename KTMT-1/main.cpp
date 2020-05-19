#include "Constants.h"
#include "QInt.h"
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	/*QInt* a, * b;
	a = new QInt(2, "111100000");
	cout << a->getBinaryType() << endl;
	b = new QInt(10, "14");
	cout << b->getBinaryType() << endl;
	delete a;
	delete b;*/
	/*cout << Number::getTwoPowerX(0);*/
	// test Number::sum
	/*cout << Number::sum("666", "456");*/

	// test getDecimal
	QInt* a;
	a = new QInt(10, "-1000");
	cout << a->getBinaryType() << endl;
	cout << a->getDecimalType() << endl;

	// test Number::subtract
	/*cout << Number::subtract("10024", "369");*/

}