#include "IOFile.h"

vector<string> IOFile::readFile(string inputFile)
{
	vector<string> input;
	ifstream infile(inputFile);
	
	if (infile.is_open()) {
		string line;
		
		while (getline(infile, line)) {
			input.push_back(line);
		}

		infile.close();
	}

	else {
		cout << "Can not open file" << endl;
	}
	return input;
}

void IOFile::writeToFile(string outputFile, vector<string>& output)
{
	ofstream outfile(outputFile);
	if (outfile.is_open()) {
		for (int i = 0; i < output.size(); i++) {
			outfile << output[i] << endl;
		}

		outfile.close();
	}

	else {
		cout << "Can not open output file" << endl;
	}
}

vector<string> IOFile::splitString(string input)
{
	vector <string> splittedString;

	// dùng stringstream để cắt chuỗi
	istringstream ss(input);
	string word;

	while(!ss.eof()) {
		ss >> word;
		splittedString.push_back(word);
	}

	// 3 dòng dưới là dùng để test phần split
	/*for (int i = 0; i < splittedWord.size(); i++) {
		cout << splittedWord[i] << endl;
	}
	cout << splittedWord.size() << endl;*/

	return splittedString;
}

string IOFile::writeOutput(int typeOfOutput, QInt& x)
{
	string result;
	switch (typeOfOutput) {
	case 2:
		result = x.getBinaryType();
		break;
	case 10:
		result = x.getDecimalType();
		break;
	case 16:
		result = x.getHexaType();
		break;
	}

	return result;
}

