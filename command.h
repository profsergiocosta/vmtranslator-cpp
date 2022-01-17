#ifndef _COMMAND_
#define _COMMAND_

#include <string>

using namespace std;

enum CommandType
{
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    C_UNDEFINED
};

bool isArithmetic(string command);

CommandType getCommandType(string command);

#endif