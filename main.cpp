#include <iostream>
#include "parser.h"
int main()
{
    std::string line;
    std::getline(std::cin, line);
    Parser parser(line);

    try
    {
        if (parser.parse())
        {
            std::cout << "Success\n";
            parser.printVars();
        }
        else
            std::cout << "Failure";
    }
    catch (const std::exception& e)
    {
        std::cout << "Parser error: " << e.what() << std::endl;
    }

    return 0;
}
