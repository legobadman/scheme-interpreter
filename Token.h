#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <cstdlib>
#include "Number.h"

enum TokenType{ ID=1, NUM, STR };

class Token
{
public:
    Token( std::string str ) : strval(strval){}
    Token( TokenType type, std::string str )
    {
        int i;
        this->type = type;
        switch(type)
        {
        case 1: strval = str;
                break;
        case 2: 
                numobj = Number(str);
                break;
        case 3: strval = str;
                break;
        default: break;
        }
    }
private:
    Number numobj;
    std::string strval;
    TokenType type;  
};

#endif
