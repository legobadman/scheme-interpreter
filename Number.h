#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <iostream>
#include <cstdlib>

enum DataType{ INT=1, FLOAT };

class Number
{
public:
    Number(){}
    Number( std::string str )
    {
        int i;
    
        this->type = INT;
        for( i=0; i<str.size(); i++ )
            if ( str[i]=='.' )
                this->type = FLOAT;
    
        if ( this->type==FLOAT )
            val.f = atof(str.c_str());
        else
            val.i = atoi(str.c_str());

    }
    int getInteger()const{ return val.i; }
    float getFloat()const{ return val.f; }
    DataType getType()const{ return type; }

    friend std::ostream &operator << ( std::ostream &out, Number num )
    {
        out << "NUM: ";
        if ( num.type == INT )
            out << num.val.i;
        else if( num.type == FLOAT )
            out << num.val.f;
        return out;
    }

private:
    union{
        float   f;
        int     i;
    }val;
    DataType type;
};


#endif
