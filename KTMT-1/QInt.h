#ifndef QINT_H
#define QINT_H

#include <vector>
#include <string>
#include "Number.h"

using namespace std;

class QInt
{
private:
	vector <bool> arrBits;
public:
	QInt(int type, string number);
	string getBinaryType();
	string getDecimalType();
	string getHexaType();
	void operator >> (int x);
	void operator << (int x);
	void rol(int x);
	void ror(int x);
	QInt operator & (QInt& other);
	QInt operator | (QInt& other);
	QInt operator ^ (QInt& other);
	QInt operator ~ ();
	QInt operator + (QInt& other);
	QInt operator - (QInt& other);
	QInt operator * (QInt& other);
	QInt operator / (QInt& other);
	QInt operator = (QInt& other);

};

#endif // !QINT_H