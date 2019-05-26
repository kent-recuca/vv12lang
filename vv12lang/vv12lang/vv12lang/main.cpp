#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "proc.h"
using namespace std;

class InputParser {
	vector <string> tokens;
public:
	InputParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i) {
			tokens.push_back(string(argv[i]));
		}
	}
	const string& getCmdOption(const string &option) const {
		vector<string>::const_iterator itr;
		itr = find(tokens.begin(), tokens.end(), option);
		if (itr != tokens.end() && ++itr != tokens.end()) {
			return *itr;
		}
		static const string empty_string("");
		return empty_string;
	}
	bool cmdOptionExists(const string &option) const {
		return find(tokens.begin(), tokens.end(), option)
			!= tokens.end();
	}
};

int main(int argc, char **argv) {
	InputParser input(argc, argv);
	const string &filename = input.getCmdOption("-f");
	if (filename.empty()) {
		vv12::Interpreter::getInp()->syntaxExit(1001, 0, "");
		return 1;
	}
	errno_t err;
	FILE* fp;
	if ((err = fopen_s(&fp, filename.c_str(), "r")) != 0) {
		vv12::Interpreter::getInp()->syntaxExit(1002, 0, "");
		return 1;
	}
	auto itp = vv12::Interpreter::getInp();
	if (itp->Compile(fp)) {
		return 1;
	}
	itp->Exec();
	itp->Delete();
	return 0;
}