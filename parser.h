#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <vector>
#include <map>


//expr ::= ++ var = expr | var ++ = expr | var = expr | add
//add  ::= term + add | term
//term ::= ++ var | var | var ++ | num


enum class Token
{
    Plus,     // +
    PlusPlus, // ++
    Var,
    Equals,   // =
    Num,
    Empty,
};

class Parser
{
private:
    std::string currentLine;
    Token token;
    std::map<std::string, int> Var;
    std::string buf;
    Token scan();
    int ExprFunc();
    int AddFunc();
    int TermFunc();

public:
    Parser(std::string line);
    ~Parser();

    bool parse();
    void printVars();


};


#endif //PARSER_H
