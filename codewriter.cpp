#include "codewriter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

CodeWriter::CodeWriter(const char *fname)
{
    out.open(fname);
    synCount = 0;
}

void CodeWriter::setFileName(string s)
{
    moduleName = s.substr(0, s.find_last_of("."));
    moduleName = moduleName.substr(s.find_last_of("/") + 1);
}

string CodeWriter::registerName(string segment, int index)
{

    if (segment == "local")
        return "LCL";
    if (segment == "argument")
        return "ARG";
    if (segment == "this")
        return "THIS";
    if (segment == "that")
        return "THAT";
    if (segment == "pointer")
        return "R" + to_string(3 + index);
    if (segment == "temp")
        return "R" + to_string(5 + index);

    return moduleName + "." + to_string(index);
}

void CodeWriter::writePush(string seg, string index)
{
    if (seg == "constant")
    {
        write("@" + index + " // push " + seg + " " + index);
        write("D=A");
        write("@SP");
        write("A=M");
        write("M=D");
        write("@SP");
        write("M=M+1");
    }
    else if (seg == "static" || seg == "temp" || seg == "pointer")
    {
        write("@" + registerName(seg, atoi(index.c_str())) + " // push " + seg + " " + index);
        write("D=M");
        write("@SP");
        write("A=M");
        write("M=D");
        write("@SP");
        write("M=M+1");
    }

    else
    {
        write("@" + registerName(seg) + " // push " + seg + " " + index);
        write("D=M");
        write("@" + index);
        write("A=D+A");
        write("D=M");
        write("@SP");
        write("A=M");
        write("M=D");
        write("@SP");
        write("M=M+1");
    }
}

void CodeWriter::writePop(string seg, string index)
{
    if (seg == "static" || seg == "temp" || seg == "pointer")
    {

        write("@SP // pop " + seg + " " + index);
        write("M=M-1");
        write("A=M");
        write("D=M");
        write("@" + registerName(seg, atoi(index.c_str())));
        write("M=D");
    }
    else
    {
        write("@" + registerName(seg) + " // pop " + seg + " " + index);
        write("D=M");
        write("@" + index);
        write("D=D+A");
        write("@R13");
        write("M=D");
        write("@SP");
        write("M=M-1");
        write("A=M");
        write("D=M");
        write("@R13");
        write("A=M");
        write("M=D");
    }
}

void CodeWriter::writeArithmetic(string command)
{
    if (command == "add")
        writeArithmeticAdd();
    else if (command == "sub")
        writeArithmeticSub();
    else if (command == "neg")
        writeArithmeticNeg();
    else if (command == "eq")
        writeArithmeticEq();
    else if (command == "gt")
        writeArithmeticGt();
    else if (command == "lt")
        writeArithmeticLt();
    else if (command == "and")
        writeArithmeticAnd();
    else if (command == "or")
        writeArithmeticOr();
    else
        writeArithmeticNot();
}

void CodeWriter::writeArithmeticAdd()
{
    write("@SP // add");
    write("M=M-1");
    write("A=M");
    write("D=M");
    write("A=A-1");
    write("M=D+M");
}

void CodeWriter::writeArithmeticSub()
{
    write("@SP // sub");
    write("M=M-1");
    write("A=M");
    write("D=M");
    write("A=A-1");
    write("M=M-D");
}

void CodeWriter::writeArithmeticNeg()
{
    write("@SP // neg");
    write("A=M");
    write("A=A-1");
    write("M=-M");
}

void CodeWriter::writeArithmeticAnd()
{
    write("@SP // and");
    write("AM=M-1");
    write("D=M");
    write("A=A-1");
    write("M=D&M");
}

void CodeWriter::writeArithmeticOr()
{
    write("@SP // or");
    write("AM=M-1");
    write("D=M");
    write("A=A-1");
    write("M=D|M");
}

void CodeWriter::writeArithmeticNot()
{

    write("@SP // not");
    write("A=M");
    write("A=A-1");
    write("M=!M");
}

void CodeWriter::writeArithmeticEq()
{
    string label("JEQ_" + moduleName + "_" + to_string(synCount));
    write("@SP // eq");
    write("AM=M-1");
    write("D=M");
    write("@SP");
    write("AM=M-1");
    write("D=M-D");
    write("@" + label);
    write("D;JEQ");
    write("D=1");
    write("(" + label + ")");
    write("D=D-1");
    write("@SP");
    write("A=M");
    write("M=D");
    write("@SP");
    write("M=M+1");

    synCount++;
}

void CodeWriter::writeArithmeticGt()
{
    string labelTrue("JGT_TRUE_" + moduleName + "_" + to_string(synCount));
    string labelFalse("JGT_FALSE_" + moduleName + "_" + to_string(synCount));

    write("@SP // gt");
    write("AM=M-1");
    write("D=M");
    write("@SP");
    write("AM=M-1");
    write("D=M-D");
    write("@" + labelTrue);
    write("D;JGT");
    write("D=0");
    write("@" + labelFalse);
    write("0;JMP");
    write("(" + labelTrue + ")");
    write("D=-1");
    write("(" + labelFalse + ")");
    write("@SP");
    write("A=M");
    write("M=D");
    write("@SP");
    write("M=M+1");

    synCount++;
}

void CodeWriter::writeArithmeticLt()
{
    string labelTrue("JLT_TRUE_" + moduleName + "_" + to_string(synCount)); // toDo ; module
    string labelFalse("JLT_FALSE_" + moduleName + "_" + to_string(synCount));

    write("@SP // lt");
    write("AM=M-1");
    write("D=M");
    write("@SP");
    write("AM=M-1");
    write("D=M-D");
    write("@" + labelTrue);
    write("D;JLT");
    write("D=0");
    write("@" + labelFalse);
    write("0;JMP");
    write("(" + labelTrue + ")");
    write("D=-1");
    write("(" + labelFalse + ")");
    write("@SP");
    write("A=M");
    write("M=D");
    write("@SP");
    write("M=M+1");

    synCount++;
}

void CodeWriter::close()
{
    out.close();
}
void CodeWriter::write(string s)
{
    out << s << endl;
}