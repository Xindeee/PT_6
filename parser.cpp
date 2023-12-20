#include "parser.h"
#include <exception>
#include <string>

Parser::Parser(std::string filename)
{
    file.open(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("filename is not valid");
    }
}
Parser::~Parser()
{

}


bool Parser::parse()
{
    while (!file.eof())
    {
        std::getline(file, currentLine);
        token = scan();
        ExprFunc();
    }
    return true;
}

Token Parser::scan()
{
    if (currentLine.empty())
    {
        return Token::Empty;
    }
    while (currentLine[0] == ' ')
    {
        currentLine.erase(0, 1);
    }
    if (currentLine[0] == '+')
    {
        if (currentLine[1] == '+')
        {
            currentLine.erase(0, 2);
            return Token::PlusPlus;
        }
        else
        {
            throw std::invalid_argument("Unsupported token");
        }
    }
    if (currentLine[0] == '=')
    {
        currentLine.erase(0, 1);
        return Token::Equals;
    }
    if (isalpha(currentLine[0]))
    {
        int i = 0;
        buf.clear();
        while (isalpha(currentLine[i]) || isdigit(currentLine[i]))
        {
            buf.push_back(currentLine[i]);
            ++i;
        }
        currentLine.erase(0, i);
        if ( Var.find(buf) == Var.end())
        {
            Var.insert(std::make_pair(buf, 0));
        }
        return Token::Var;
    }
    if (isdigit(currentLine[0]))
    {
        int i = 0;
        buf.clear();
        while (isdigit(currentLine[i]))
        {
            buf.push_back(currentLine[i]);
            ++i;
        }
        currentLine.erase(0, i);
        return Token::Num;
    }
    throw std::invalid_argument("Unsupported token");
}


void Parser::printVars()
{
    for (std::pair<const std::basic_string<char>, int> i : Var)
    {
        std::cout << i.first << '=' << i.second << '\n';
    }
}

int Parser::ExprFunc()
{
    if (token == Token::PlusPlus)
    {
        token = scan();
        if (token == Token::Var)
        {
            token = scan();
            return Expr1Func();
        }
        else
            throw std::invalid_argument("Error");
    }
    else if (token == Token::Var)
    {
        token = scan();
        return Expr2Func();
    }
    else if (token == Token::Num)
    {
        token = scan();
        if (token != Token::Empty)
            throw std::invalid_argument("Error");
        return std::stoi(buf);
    }
    throw std::invalid_argument("Error");
}

int Parser::Expr1Func()
{
    if (token == Token::Equals)
    {
        std::string a = buf;
        token = scan();
        Var.at(a) = ExprFunc();
        return Var.at(a);
    }
    else if (token == Token::Empty)
    {
        return Var.at(buf);
    }
    throw std::invalid_argument("Error");
}

int Parser::Expr2Func()
{
    if (token == Token::Equals)
    {
        std::string a = buf;
        token = scan();
        Var.at(a) = ExprFunc();
        return Var.at(a);
    }
    else if (token == Token::Empty)
    {
        return Var.at(buf);
    }
    else if (token == Token::PlusPlus)
    {
        Var.at(buf)++;
        token = scan();
        if (token != Token::Empty)
            throw std::invalid_argument("Error");
        return Var.at(buf);
    }
}

