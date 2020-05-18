#include "Constants.h"
#include "QInt.h"
#include <iostream>

using namespace std;

int main() {
	QInt* a, * b;
	a = new QInt(2, "111100000");
	cout << a->getBinaryType() << endl;
	b = new QInt(10, "14");
	cout << b->getBinaryType() << endl;
	cout << "LONG" << endl;
	delete a;
	delete b;
}