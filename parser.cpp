#include "parser.h"
#include <exception>
#include <string>
#include <format>

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
            currentLine.erase(0, 1);
            return Token::Plus;
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
    std::string var_name;

    if (token == Token::PlusPlus)
    {
        token = scan();
        if (token == Token::Var)
        {
            var_name = buf;
            token = scan();
            if (token == Token::Equals)
            {
                token = scan();
                Var[var_name] = ExprFunc();
                return ++Var[var_name];
            }
            else
            {
                int sum = 0;
                if (token == Token::Plus)
                {
                    token = scan();
                    sum += AddFunc();
                }
                return sum + ++Var[var_name];
            }
        }
        throw std::invalid_argument("Error");
    }
    else if (token == Token::Var)
    {
        var_name = buf;
        bool incr = false;
        token = scan();
        if (token == Token::PlusPlus)
        {
            incr = true;
            token = scan();
        }
        if (token == Token::Equals)
        {
            token = scan();
            Var[var_name] = ExprFunc();
            if (incr)
                return Var[var_name]++;
            else
                return Var[var_name];
        }
        else
        {
            int sum = 0;
            if (token == Token::Plus)
            {
                token = scan();
                sum += AddFunc();
            }
            if (incr)
                return sum + Var[var_name]++;
            else
                return sum + Var[var_name];
        }
    }
    else if (token == Token::Empty)
        return 0;
    else
        return AddFunc();
    throw std::invalid_argument("Error");
}

int Parser::AddFunc()
{
    int sum = TermFunc();

    if (token == Token::Plus)
    {
        token = scan();
        sum += AddFunc();
    }

    return sum;
}

int Parser::TermFunc()
{
    if (token == Token::PlusPlus)
    {
        token = scan();
        if (token == Token::Var)
        {
            token = scan();
            return ++Var[buf];
        }
    }
    else if (token == Token::Var)
    {
        bool incr = false;
        token = scan();
        if (token == Token::PlusPlus)
        {
            incr = true;
            token = scan();
        }

        if (incr)
            return Var[buf]++;
        else
            return Var[buf];
    }
    else if (token == Token::Num)
        return std::stoi(buf);
    throw std::invalid_argument("Error");
}
