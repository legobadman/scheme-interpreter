#include "Number.h"

Number::Number( std::string str )
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

Number::Number( int i ) 
    {
        val.i = i;    
        type = INT;
    }

Number::Number( float f )
    {
        val.f = f;
        type = FLOAT;
    }

std::ostream &operator << ( std::ostream &out, Number num )
{
    out << "NUM: ";
    if ( num.type == INT )
        out << num.val.i;
    else if( num.type == FLOAT )
        out << num.val.f;
    return out;
}

Number Number::operator + (const Number &numobj)
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

Number Number::operator - (const Number &numobj)
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

Number Number::operator * (const Number &numobj)
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

Number Number::operator / (const Number &numobj)
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
