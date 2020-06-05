//#include "Constants.h"
//#include "QInt.h"
//#include "IOFile.h"
//#include <iostream>
//
//using namespace std;
//
//int main() {
//
//	// Test phần input và output
//	// Sửa maxlength trong constant thành 8 bit cho dễ test ## 2^7 = 128
//
//	//QInt* a;
//	//a = new QInt(2, "11111110");
//	//cout << a->getBinaryType() << endl;
//	////cout << a->getDecimalType() << endl;
//	//cout << a->getHexaType() << endl;
//	//delete a;
//	//a = new QInt(10, "-120");
//	//cout << a->getBinaryType() << endl;
//	//cout << a->getHexaType() << endl;
//	///*cout << a->getDecimalType() << endl;*/
//	//delete a;
//	//a = new QInt(16, "7F");
//	//cout << a->getBinaryType() << endl;
//	//cout << a->getDecimalType() << endl;
//	//delete a;
//
//	//QInt a(2, "11011");
//	//QInt b(2, "111");
//	//QInt c = a - b;
//	//cout << c.getBinaryType() << endl;
//
//	// a, b để đọc dữ liệu, c để chứa kết quả
//	QInt* a, * b;
//	QInt c(2, "");
//
//
//
//	// dùng để test
//	/*a = new QInt(2, "100");
//	b = new QInt(2, "11111110");
//
//	~*b;
//	cout << b->getBinaryType() << endl;*/
//
//
//
//
//	// vector input chứa các dòng được đọc từ file input.txt
//	// File input.txt có thể được sửa trong Constants.h
//	vector<string> input = IOFile::readFile(Constants::inputFile);
//
//	// Duyệt qua từng dòng ở vector input để thực hiện từng yêu cầu, kết quả result sẽ được ghi vào vector output
//	vector<string> output;
//	string result;
//
//	for (int i = 0; i < input.size(); i++) {
//
//		// Tách từng từ trong từng dòng ra
//		vector<string> splittedString;
//		splittedString = IOFile::splitString(input[i]);
//
//
//		int typeOfInput, typeOfOutput;
//		string typeOfOperator;
//		int numberOfShift = 0;
//
//		if (splittedString.size() == 4) {
//		
//			// Chuyển từ string sang int
//			typeOfInput = typeOfOutput = atoi(splittedString[0].c_str());
//
//			typeOfOperator = splittedString[2];
//
//			if (typeOfOperator == "&" || typeOfOperator == "|" || typeOfOperator == "^" || typeOfOperator == "+" || typeOfOperator == "-"|| 
//				typeOfOperator == "*" || typeOfOperator == "/") {
//
//				a = new QInt(typeOfInput, splittedString[1]);
//				b = new QInt(typeOfInput, splittedString[3]);
//
//				if (typeOfOperator == "&") {
//					c = (*a & *b);
//				}
//				else if (typeOfOperator == "|") {
//					c = (*a | *b);
//				}
//				else if (typeOfOperator == "^") {
//					c = (*a ^ *b);
//				}
//				else if (typeOfOperator == "+") {
//					try {
//						c = (*a + *b);
//					}
//					catch (int e) {
//						QInt d(2, "0");
//						c = d;
//					}
//				}
//				else if (typeOfOperator == "-") {
//					try {
//						c = (*a - *b);
//					}
//					catch (int e) {
//						QInt d(2, "0");
//						c = d;
//					}
//				}
//				else if (typeOfOperator == "*") {
//					try {
//						c = (*a * *b);
//					}
//					catch (int e) {
//						QInt d(2, "0");
//						c = d;
//					}
//				}
//				else if (typeOfOperator == "/") {
//					try {
//						c = (*a / *b);
//					}
//					catch (int e) {
//						QInt d(2, "0");
//						c = d;
//					}
//				}
//
//				// Ghi kết quả vào vector ouput
//				result = IOFile::writeOutput(typeOfOutput, c);
//
//				// Xóa 2 biến a và b
//				delete a;
//				delete b;
//			}
//
//			else { // Trường hợp >> << thì đọc khác
//				a = new QInt(typeOfInput, splittedString[1]);
//				numberOfShift = atoi(splittedString[3].c_str());
//				typeOfOperator = splittedString[2];
//				
//				if (typeOfOperator == ">>") {
//					*a >> numberOfShift;
//				}
//				else if (typeOfOperator == "<<") {
//					*a << numberOfShift;
//				}
//
//				// Ghi kết quả vào vector ouput
//				result = IOFile::writeOutput(typeOfOutput, *a);
//
//				// Xóa con trỏ a
//				delete a;
//			}
//		}
//
//
//		// Các phép toán ror, rol, ~, và chuyển hệ số
//		else if (splittedString.size() == 3) { 
//			typeOfOperator = splittedString[1];
//			if (typeOfOperator == "ror" || typeOfOperator == "rol" || typeOfOperator == "~") {
//				// Chuyển từ string sang int
//				typeOfInput = typeOfOutput = atoi(splittedString[0].c_str());
//
//				// Đọc số vào 
//				a = new QInt(typeOfInput, splittedString[2]);
//
//				// Xử lý theo yêu cầu
//				if (typeOfOperator == "ror") {
//					a->ror();
//				}
//				else if (typeOfOperator == "rol") {
//					a->rol();
//				}
//				else if (typeOfOperator == "~") {
//					~*a;
//				}
//
//				// Ghi kết quả vào vector ouput
//				result = IOFile::writeOutput(typeOfOutput, *a);
//
//				// Xóa con trỏ a
//				delete a;
//			}
//
//			else {
//				typeOfInput = atoi(splittedString[0].c_str());
//				typeOfOutput = atoi(splittedString[1].c_str());
//
//				a = new QInt(typeOfInput, splittedString[2]);
//
//				// Ghi kết quả vào vector ouput
//				result = IOFile::writeOutput(typeOfOutput, *a);
//
//				// Xóa con trỏ a
//				delete a;
//			}
//		}
//
//		// Không xảy ra trường hợp này, để đây để đề phòng bất trắc
//		else { 
//			
//		}
//
//		// push result vào output
//		output.push_back(result);
//	}
//
//	// Ghi output ra file output.txt
//	IOFile::writeToFile(Constants::outputFile, output);
//
//	return 0;
//}


#include<iostream>
#include"QInt.h"

using namespace std;
int main() {
	QInt b(2, "01");
	QInt a(10, "-2");
	cout << (a + b).getBinaryType() << endl;
	return 0;
}