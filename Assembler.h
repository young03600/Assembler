#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

class Assembler
{
public:
	Assembler(const string);
	~Assembler();

	void run();
private:
	void read();
	void interpret();

	char find_type(const string &);
	int lable_offset(const vector<string>::iterator &, const vector<string>::iterator &, const string &);

	vector<string> inst;
	vector<string> track;
	string *fileName;

	int count;
};

#endif // !ASSEMBLER_H