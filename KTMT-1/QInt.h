#ifndef QINT_H
#define QINT_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Constants.h"
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
	void rol();
	void ror();
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