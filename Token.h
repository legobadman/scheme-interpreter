#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <cstdlib>
#include "Number.h"

enum TokenType{ ID=1, NUM, STR, BRACKET, OPERATOR, ROP };

class Token
{
public:
    Token()=default;
    Token( std::string str ) : strval(strval){}
    Token( TokenType type, std::string str ) : type(type), strval(str)
    {
        if ( type == NUM )
            numobj = Number(str);
    }

    Token( Number num ) : type(NUM), numobj(num) {}
    Token( int integer ) : type(NUM), strval("NUM"), numobj(integer) {}
    Token( float f ) : type(NUM), strval("NUM"), numobj(f) {}

    std::string getStrval() const { return strval; }
    TokenType   getTokenType() const { return type; }
    friend std::ostream &operator << ( std::ostream& out, Token tt )
    {
        switch(tt.type)
        {
        case ID:    out << "ID: " << tt.strval;break;
        case NUM:   out << tt.numobj; break;
        case STR:   out << "STR: " << tt.strval; break;
        case BRACKET:   out << "BRACKET: " << tt.strval; break;
        case OPERATOR:  out << "OPERATOR: " << tt.strval; break;
        case ROP:       out << "ROP: " << tt.strval; break;
        default: out << "error(), what the token is !"; break;
        }
        return out;
    }

    Number &getNumber()
    {
        return numobj;
    }

private:
    TokenType type;  
    std::string strval;
    Number numobj;
};

#endif
