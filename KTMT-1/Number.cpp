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

    string result;
    int temp = 0;
    int multResult;
    for (int i = number.length() - 1; i >= 0; i--) {
        multResult = (number[i] - '0') * 2 + temp;
        temp = multResult / 10;
        multResult %= 10;
        result.insert(0, to_string(multResult));
    }
    if (temp != 0)
        result.insert(0, to_string(temp));
    return result;
}

string Number::getTwoPowerX(int x)
{
    int startPos = -1;
    if (!Number::twoPowerX[x].empty()) return  Number::twoPowerX[x];
    for (int i = x - 1; i >= 0; i--) {
        if (!Number::twoPowerX[i].empty()) {
            startPos = i;
            break;
        }
    }
    for (int i = startPos + 1; i <= x; i++) {
        Number::twoPowerX[i] = Number::mult2(Number::twoPowerX[i - 1]);
    }
    return Number::twoPowerX[x];
}

string Number::sum(string x, string y)
{
    string result;
    // x lúc nào cũng dài hơn hoặc bằng y
    if (x.length() < y.length()) {
        string stringTemp = x;
        x = y;
        y = stringTemp;
    }
    int temp = 0;
    for (int i = x.length() - 1, j = y.length() - 1; j >= 0; i--, j--) {
        int sumResult = (x[i] - '0') + (y[j] - '0') + temp;
        temp = sumResult / 10;
        sumResult %= 10;
        result.insert(0, to_string(sumResult));
    }
    for (int i = x.length() - y.length() - 1; i >= 0; i--) {
        int sumResult = (x[i] - '0') + temp;
        temp = sumResult / 10;
        sumResult %= 10;
        result.insert(0, to_string(sumResult));
    }

    // nếu vẫn còn temp
    if (temp) {
        result.insert(0, to_string(temp));
    }
    return result;
}

//string Number::subtract(string x, string y)
//{
//    int numX = 0, numY = 0, temp = 0, subResult = 0;
//    string result;
//    for (int i = x.length() - 1, j = y.length() - 1; j >= 0; i--, j--) {
//        numX = x[i] - '0';
//        numY = y[j] - '0' + temp;
//        if (numX < numY) {
//            numX += 10;
//            temp = 1;
//        }
//        else temp = 0;
//        subResult = numX - numY;
//        result.insert(0, to_string(subResult));
//    }
//    for (int i = x.length() - y.length() - 1; i >= 0; i--) {
//        numX = x[i] - '0';
//        numY = temp;
//        if (numX < numY) {
//            numX += 10;
//            temp = 1;
//        }
//        else temp = 0;
//        subResult = numX - numY;
//        result.insert(0, to_string(subResult));
//    }
//    while (result[0] == '0') result.erase(0, 1);
//    return result;
//}

unordered_map<char, string> Number::initHexMap()
{
    unordered_map<char, string> umap;
    umap['0'] = "0000";
    umap['1'] = "0001";
    umap['2'] = "0010";
    umap['3'] = "0011";
    umap['4'] = "0100";
    umap['5'] = "0101";
    umap['6'] = "0110";
    umap['7'] = "0111";
    umap['8'] = "1000";
    umap['9'] = "1001";
    umap['A'] = "1010";
    umap['B'] = "1011";
    umap['C'] = "1100";
    umap['D'] = "1101";
    umap['E'] = "1110";
    umap['F'] = "1111";
    return umap;
}

char Number::getHexFromBinary(string bin)
{
    auto it = hexMap.begin();
    while (it != hexMap.end()) {
        if (it->second == bin) {
            return it->first;
        }
        it++;
    }
}

void Number::toTwoComplement(vector<bool>& arrBits) {
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
    
    // nếu chuyển sang số âm thì phải thêm các số 1 vô trước
    while (arrBits.size() < Constants::maxLength) {
        arrBits.insert(arrBits.begin(), 1);
    }
    
    // trường hợp đổi từ số âm thành số dương thì xóa các số 0 đứng đầu
    while (arrBits.size() && !arrBits[0])

    while (arrBits.size() > 1 && arrBits[0] == 0)
    {

        arrBits.erase(arrBits.begin());
    }
}
