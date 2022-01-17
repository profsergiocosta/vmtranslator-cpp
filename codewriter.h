#ifndef CODEWRITER_H_INCLUDED
#define CODEWRITER_H_INCLUDED

#include <fstream>
#include <string>

#include "command.h"

using namespace std;

class CodeWriter
{

public:
	CodeWriter(const char *fname);
	void setFileName(string s);
	void writeArithmetic(string command);
	void writePushPop(CommandType type, string seg, string index);
	void close();

	void writePush(string seg, string index);
	void writePop(string seg, string index);
	void writeArithmeticAdd();
	void writeArithmeticSub();
	void writeArithmeticNeg();
	void writeArithmeticEq();
	void writeArithmeticGt();
	void writeArithmeticLt();
	void writeArithmeticAnd();
	void writeArithmeticOr();
	void writeArithmeticNot();

private:
	string registerName(string segment, int index = 0);
	void write(string s);

	int synCount;
	ofstream out;
	string moduleName;
};
#endif
