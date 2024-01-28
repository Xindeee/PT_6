#include <iostream>
#include "parser.h"
int main()
{
    Parser parser("file");
    if (parser.parse())
    {
        std::cout << "Success\n";
        parser.printVars();
    }
    else
        std::cout << "Failure";
}