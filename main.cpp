
#include <fstream>
#include <iostream>
#include <string>

#include "command.h"
#include "parser.h"
#include "codewriter.h"

using namespace std;

int main(int argc, char **argv)
{

    if (argc < 2)
        exit(1);

    string input = string(argv[1]);
    Parser *parser = new Parser(input.c_str());
    string output = input.substr(0, input.find_last_of(".")) + ".asm";
    CodeWriter *codeWriter = new CodeWriter(output.c_str());

    string arg1, arg2;

    parser->advance();
    while (parser->hasMoreCommands())
    {

        switch (parser->commandType())
        {

        case C_ARITHMETIC:
            codeWriter->writeArithmetic(parser->arg1());
            //cout << parser->arg1() << endl;
            break;

        case C_PUSH:
            arg1 = parser->arg1();
            arg2 = parser->arg2();
            //cout << "push " << arg1 << "-" << arg2 << endl;
            codeWriter->writePush(arg1, arg2);
            break;
        case C_POP:
            arg1 = parser->arg1();
            arg2 = parser->arg2();
            //cout << "pop " << arg1 << "-" << arg2 << endl;
            codeWriter->writePop(arg1, arg2);
            break;

        default:
            break;
        }
        parser->advance();
    }

    return 0;
}
