#include "Number.h"
#include "Constants.h"

vector<bool> Number::inputBinary(string number)
{
	vector<bool> arrBits;
	for (int i = 0; i < number.length(); i++) {
		if (arrBits.size() == Constants::maxLength) break;
		arrBits.push_back(number[i] - '0');
	}
	return arrBits;
}

vector<bool> Number::inputDecimal(string number)
{
    vector<bool> arrBits;
    bool overflowCase = false;
    bool bit, isNegative = false;
    if (number[0] == '-') {
        isNegative = true;
        number.erase(0, 1);
    }
    while (number != "") {
        bit = (number[number.length() - 1] - '0') % 2;
        if (arrBits.size() == Constants::maxLength - 1) {
            vector <bool> foo(Constants::maxLength - 1, 1);
            arrBits = foo;
            arrBits.insert(arrBits.begin(), 0);
            overflowCase = true;
            break;
        }
        arrBits.insert(arrBits.begin(), bit);
        number = Number::div2(number);
    }

    if (isNegative) {
        if (overflowCase) {
            vector <bool> foo(Constants::maxLength - 1, 0);
            arrBits = foo;
            arrBits.insert(arrBits.begin(), 1);
        }
        int pos = -1;
        for (int i = arrBits.size() - 1; i >= 0; i--) {
            if (arrBits[i]) {
                pos = i;
                break;
            }
        }
        for (int i = pos - 1; i >= 0; i--) {
            arrBits[i] = !arrBits[i];
        }
        while (arrBits.size() < Constants::maxLength) {
            arrBits.insert(arrBits.begin(), 1);
        }
    }
    return arrBits;
}

vector<bool> Number::inputHexa(string number)
{
    vector<bool> arrBits;
    return arrBits;
}

string Number::div2(string number)
{
    string result;
    int temp = 0, quotient; // quotient = thương
    for (int i = 0; i < number.length(); i++) {
        temp = temp * 10 + (number[i] - '0');
        quotient = temp / 2;
        temp %= 2;
        result += to_string(quotient);
    }
    while (result[0] == '0')
        result.erase(0, 1);
    return result;
}

void Number::removeZeroPrefix(vector<bool>& arrBits)
{
    while (arrBits.size() > 1 && arrBits[0] == 0)
    {
        arrBits.erase(arrBits.begin());
    }
}
