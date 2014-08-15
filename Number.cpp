#include "Number.h"

Number::Number( std::string str )
{
    int i;
    
    this->type = INT;
    for( i=0; i<str.size(); i++ )
        if ( str[i]=='.' )
            this->type = FLOAT;
 
    if ( this->type==FLOAT )
        f = atof(str.c_str());
    else
        this->i = atoi(str.c_str());

}

Number::Number( int i ) 
{
    i = i;    
    type = INT;
}

Number::Number( float f )
{
    f = f;
    type = FLOAT;
}

std::ostream &operator << ( std::ostream &out, Number num )
{
    out << "NUM: ";
    if ( num.type == INT )
        out << num.i;
    else if( num.type == FLOAT )
        out << num.f;
    return out;
}

Number Number::operator + (const Number &numobj)
{
    return Number( ((type==INT)? i : f) +
                    ((numobj.type==INT)? numobj.i : numobj.f));
}

Number Number::operator - (const Number &numobj)
{
    return Number( ((type==INT)? i : f) -
                    ((numobj.type==INT)? numobj.i : numobj.f));
}

Number Number::operator * (const Number &numobj)
{
    return Number( ((type==INT)? i : f) *
                    ((numobj.type==INT)? numobj.i : numobj.f));
}

Number Number::operator / (const Number &numobj)
{
    return Number( ((type==INT)? i : f) /
                    ((numobj.type==INT)? numobj.i : numobj.f));
}

bool Number::operator < (const Number &numobj)
{
    return (((type==INT)? i : f) < 
                ((numobj.type==INT)?numobj.i : numobj.f));
}

bool Number::operator <= (const Number &numobj)
{
    return (((type==INT)? i : f) <=
                ((numobj.type==INT)? numobj.i : numobj.f));
}

bool Number::operator > (const Number &numobj)
{
    return ((type==INT)?i:f ) > ((numobj.type==INT)? numobj.i : numobj.f);
}

bool Number::operator >= (const Number &numobj)
{
    return ((type==INT)? i : f) >= ((numobj.type==INT)? numobj.i : numobj.f);
}

bool Number::operator == (const Number &numobj)
{
    return ((type==INT)? i : f) == ((numobj.type==INT)? numobj.i : numobj.f);
}



