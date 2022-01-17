
#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const char *nome)
{
    arq.open(nome);
}

bool Parser::hasMoreCommands()
{
    return !arq.eof() && currentCommand != "EOF";
}

void Parser::advance()
{

    currentCommand = nextToken();
}

string Parser::nextToken()
{
    if (!arq.eof())
    {
        arq >> currentCommand;
        if (arq.eof()) return "EOF";

        if (currentCommand.substr(0, 2) == "//")
        {
            arq.ignore(10000, '\n');
            return nextToken();
        }
        else
            return currentCommand;
    }
    else
        return "";
}

CommandType Parser::commandType()
{
    return getCommandType(currentCommand);
}

string Parser::arg1()
{

    CommandType type = commandType();
    if (type == C_ARITHMETIC)
        return currentCommand;
    else
        return nextToken();
}
string Parser::arg2()
{
    return nextToken();
}
