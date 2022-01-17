#ifndef _PARSER_H_
#define _PARSER_H_


#include <fstream>
#include <string>

#include "command.h"

using namespace std;

class Parser
{
private:
    ifstream arq;
   

public:
    Parser(const char *nome);
    bool hasMoreCommands();
    string nextToken();
    void advance();
    CommandType commandType();
    string arg1();
    string arg2();

     string currentCommand;
};

#endif