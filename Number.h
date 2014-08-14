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
    Number( int i ) 
    {
        val.i = i;    
        type = INT;
    }
    Number( float f )
    {
        val.f = f;
        type = FLOAT;
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

    
    Number operator + (const Number &numobj)
    {
        if( this->type==FLOAT )
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.f + numobj.val.f) );
            else
                return Number( (float)(val.f + numobj.val.i) );
        }
        else
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.i + numobj.val.f) );
            else
                return Number( (int)(val.i + numobj.val.i) );
        }
    }
    Number operator - (const Number &numobj)
    {
        if( this->type==FLOAT )
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.f - numobj.val.f) );
            else
                return Number( (float)(val.f - numobj.val.i) );
        }
        else
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.i - numobj.val.f) );
            else
                return Number( (int)(val.i - numobj.val.i) );
        }
    }
    Number operator * (const Number &numobj)
    {
        if( this->type==FLOAT )
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.f * numobj.val.f) );
            else
                return Number( (float)(val.f * numobj.val.i) );
        }
        else
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.i * numobj.val.f) );
            else
                return Number( (int)(val.i * numobj.val.i) );
        }
    }
    Number operator / (const Number &numobj)
    {
        if( this->type==FLOAT )
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.f / numobj.val.f) );
            else
                return Number( (float)(val.f / numobj.val.i) );
        }
        else
        {
            if( numobj.type == FLOAT )
                return Number( (float)(val.i / numobj.val.f) );
            else
                return Number( (int)(val.i / numobj.val.i) );
        }
    }

private:
    union{
        float   f;
        int     i;
    }val;
    DataType type;
};


#endif
