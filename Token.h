#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <cstdlib>
#include "Number.h"

enum TokenType{ ID=1, NUM, STR, BRACKET, OPERATOR, ROP };

class Token
{
public:
    Token( std::string str ) : strval(strval){}
    Token( TokenType type, std::string str ) : type(type), strval(str)
    {   
        if ( type == NUM )
            numobj = Number(str);
    }
    std::string getStrval() const { return strval; }
    TokenType   getTokenType() const { return type; }
    friend std::ostream &operator << ( std::ostream& out, Token tt )
    {
        switch(tt.type)
        {
        case ID:    out << "ID: " << tt.strval << std::endl;break;
        case NUM:   out << tt.numobj; break;
        case STR:   out << "STR: " << tt.strval << std::endl; break;
        case BRACKET:   out << "BRACKET: " << tt.strval << std::endl; break;
        case OPERATOR:  out << "OPERATOR: " << tt.strval << std::endl; break;
        case ROP:       out << "ROP: " << tt.strval << std::endl; break;
        default: out << "error(), what the token is !" << std::endl; break;
        }
        return out;
    }

private:
    TokenType type;  
    std::string strval;
    Number numobj;
};

#endif
