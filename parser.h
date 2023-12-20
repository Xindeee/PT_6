#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


//Expr ::= ++Var Expr1 | Var Expr2 | Num
//Expr1 ::= ε | = Expr
//Expr2 ::= ε | = Expr | ++


enum class Token
{
    PlusPlus, // ++
    Var,
    Equals, // =
    Num,
    Empty,
};

class Parser
{
private:
    std::string currentLine;
    Token token;
    std::ifstream file;
    std::map<std::string, int> Var;
    std::string buf;
    Token scan();
    int ExprFunc();
    int Expr1Func();
    int Expr2Func();

public:
    Parser(std::string filename);
    ~Parser();

    bool parse();
    void printVars();


};


#endif //PARSER_H