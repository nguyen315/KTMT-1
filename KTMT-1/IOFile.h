#ifndef IOFILE_H
#define IOFILE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "QInt.h"

using namespace std;

class IOFile
{
public:
	static vector<string> readFile(string inputFile);
	//static void writeToFile(string outputFile, vector<string>& output);
	static vector<string> splitString(string input);
	static string writeOutput(int typeOfOutput, QInt& x);
};

#endif // !IOFILE_H