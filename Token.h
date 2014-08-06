#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <cstdlib>
#include "Number.h"

enum TokenType{ ID=1, NUM, STR, BRACKET, OPERATOR };

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
        if ( tt.type==ID )
        {
            out << "ID: " << tt.strval << std::endl;
        }
        else if ( tt.type==NUM )
        {
            out << tt.numobj;
        }
        else if ( tt.type==STR )
        {
            out << "STR: " << tt.strval << std::endl;
        }
        else if ( tt.type==BRACKET )
        {
            out << "BRACKET: " << tt.strval << std::endl;
        }
        else if ( tt.type==OPERATOR )
        {
            out << "OPERATOR: " << tt.strval << std::endl;
        }
        return out;
    }

private:
    TokenType type;  
    std::string strval;
    Number numobj;
};

#endif
