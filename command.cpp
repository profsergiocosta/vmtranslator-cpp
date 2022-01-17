

#include "command.h"

#include <set>
#include <map>
#include <string>

using namespace std;

set<string> arithmetic{
    "add",
    "sub",
    "neg",
    "eq",
    "gt",
    "lt",
    "and",
    "or",
    "not"};

bool isArithmetic(string command)
{
    return arithmetic.find(command) != arithmetic.end();
}

map<string, CommandType>
    commands = {
        {"push", C_PUSH},
        {"pop", C_POP},
        {"label", C_LABEL},
        {"goto", C_GOTO},
        {"if-goto", C_IF},
        {"function", C_FUNCTION},
        {"return", C_RETURN},
        {"call", C_CALL},
};

CommandType getCommandType(string command)
{

    if (isArithmetic(command))
        return C_ARITHMETIC;
    else
        return commands[command];
}
