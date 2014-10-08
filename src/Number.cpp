#include "Number.h"
#include <cstdlib>

Number::Number (std::string str)
{
    int i;
    int numer_pos, denom_pos;
    int isPositive;
    
    this->type = INT;

    for( i=0; i<str.size(); i++ )
    {
        if ( str[i]=='.' )
        {
            type = FLOAT;
        }
        else if( str[i]=='/' )
        {
            numer_pos = i;
            type = FRACTION;
            denom_pos = str.size();
        }
    }
    if ( type==FLOAT )
    {
        f = atof(str.c_str());
    }
    else if( type==FRACTION )
    {
        int numer = atoi(str.substr(0,numer_pos).c_str());
        int denom = atoi(str.substr(numer_pos+1,denom_pos).c_str());
        
        this->ff = Fraction( numer, denom );
        this->type=FRACTION;
    }
    else
    {
        this->i = atoi(str.c_str());
        this->type=INT;
    }
}

Number::Number (int ii) : i(ii), type(INT)
{
}

Number::Number (float ff) : f(ff), type(FLOAT) {}

Number::Number (int numer, int denom)
{
    if( numer % denom==0 )
    {
        type = INT;
        i = numer / denom;
    }
    else
    {
        type = FRACTION;
        ff = Fraction(numer, denom);
    }
}

Number::Number (Fraction f)
{
    if( f.numer % f.denom == 0 )
    {
        type = INT;
        i = f.numer % f.denom;
    }
    else
    {
        type = FRACTION;
        ff = Fraction( f );
    }
}

std::ostream &operator << ( std::ostream &out, Number num )
{
    if ( num.type == INT )
        out << num.i;
    else if( num.type == FLOAT )
        out << num.f;
    else
        out << num.ff;
    return out;
}

Number Number::operator+ (const Number &numobj)
{
    Fraction sum;
    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return Number( i+numobj.i );
        case FLOAT:
            return Number( i+numobj.f );
        case FRACTION:
            sum = numobj.ff + i;
            return Number( sum.numer, sum.denom );
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return Number( f+numobj.i );
        case FLOAT:
            return Number( f+numobj.f );
        case FRACTION:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        }
        break;
    case FRACTION:
        switch(numobj.type)
        {
        case INT:
            sum = ff + numobj.i;
            return Number( sum.numer, sum.denom );
        case FLOAT:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        case FRACTION:
            sum = ff + numobj.ff;
            return Number( sum.numer, sum.denom );
        }
        break;
    default:
        break;
    }
}

Number Number::operator - (const Number &numobj)
{
    Fraction sum;
    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return Number( i-numobj.i );
        case FLOAT:
            return Number( i-numobj.f );
        case FRACTION:
            sum = i - numobj.ff;
            return Number( sum.numer, sum.denom );
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return Number( f-numobj.i );
        case FLOAT:
            return Number( f-numobj.f );
        case FRACTION:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        }
        break;
    case FRACTION:
        switch(numobj.type)
        {
        case INT:
            sum = ff - numobj.i;
            return Number( sum.numer, sum.denom );
        case FLOAT:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        case FRACTION:
            sum = ff - numobj.ff;
            return Number( sum.numer, sum.denom );
        }
        break;
    default:
        break;
    }
}

Number Number::operator * (const Number &numobj)
{
    Fraction sum;
    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return Number( i*numobj.i );
        case FLOAT:
            return Number( i*numobj.f );
        case FRACTION:
            sum = numobj.ff * i;
            return Number( sum.numer, sum.denom );
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return Number( f*numobj.i );
        case FLOAT:
            return Number( f*numobj.f );
        case FRACTION:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        }
        break;
    case FRACTION:
        switch(numobj.type)
        {
        case INT:
            sum = ff * numobj.i;
            return Number( sum.numer, sum.denom );
        case FLOAT:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        case FRACTION:
            sum = ff * numobj.ff;
            return Number( sum.numer, sum.denom );
        }
        break;
    default:
        break;
    }
}

Number Number::operator / (const Number &numobj)
{
    Fraction sum;
    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return Number( i, numobj.i );
        case FLOAT:
            return Number( i/numobj.f );
        case FRACTION:
            sum = numobj.ff / i;
            return Number( sum.numer, sum.denom );
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return Number( f / numobj.i );
        case FLOAT:
            return Number( f / numobj.f );
        case FRACTION:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        }
        break;
    case FRACTION:
        switch(numobj.type)
        {
        case INT:
            sum = ff / numobj.i;
            return Number( sum.numer, sum.denom );
        case FLOAT:
            cerr << "error sum between float type and fraction type" << endl;
            exit(0);
        case FRACTION:
            sum = ff / numobj.ff;
            return Number( sum.numer, sum.denom );
        }
        break;
    default:
        break;
    }
}


bool Number::operator < (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i < numobj.i ;
        case FLOAT:
            return i < numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i < fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f < numobj.i;
        case FLOAT:
            return f < numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f < fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float < numobj.i;

        case FLOAT:
            return fraction_to_float < numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float < fraction_to_float2;
        }
        break;
    default:
        break;
    }



}

bool Number::operator <= (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i <= numobj.i ;
        case FLOAT:
            return i <= numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i <= fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f <= numobj.i;
        case FLOAT:
            return f <= numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f <= fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float <= numobj.i;

        case FLOAT:
            return fraction_to_float <= numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float <= fraction_to_float2;
        }
        break;
    default:
        break;
    }



}

bool Number::operator > (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i > numobj.i ;
        case FLOAT:
            return i > numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i > fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f > numobj.i;
        case FLOAT:
            return f > numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f > fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float > numobj.i;

        case FLOAT:
            return fraction_to_float > numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float < fraction_to_float2;
        }
        break;
    default:
        break;
    }



}

bool Number::operator >= (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i >= numobj.i ;
        case FLOAT:
            return i >= numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i >= fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f >= numobj.i;
        case FLOAT:
            return f >= numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f >= fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float >= numobj.i;

        case FLOAT:
            return fraction_to_float >= numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float >= fraction_to_float2;
        }
        break;
    default:
        break;
    }



}

bool Number::operator == (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i == numobj.i ;
        case FLOAT:
            return i == numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i == fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f == numobj.i;
        case FLOAT:
            return f == numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f == fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float == numobj.i;

        case FLOAT:
            return fraction_to_float == numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float == fraction_to_float2;
        }
        break;
    default:
        break;
    }



}

bool Number::operator != (const Number &numobj)
{
    Fraction sum;
    float fraction_to_float, fraction_to_float2;

    switch(type)
    {
    case INT:
        switch(numobj.type)
        {
        case INT:
            return i != numobj.i ;
        case FLOAT:
            return i != numobj.f ;
        case FRACTION:
            fraction_to_float  = (float) numobj.ff.numer / numobj.ff.denom;
            return i != fraction_to_float; 
        }
        break;
    case FLOAT:
        switch(numobj.type)
        {
        case INT:
            return f != numobj.i;
        case FLOAT:
            return f != numobj.f;
        case FRACTION:
            fraction_to_float = (float) numobj.ff.numer / numobj.ff.denom;
            return f != fraction_to_float;
        }
        break;
    case FRACTION:
        fraction_to_float = (float) ff.numer / ff.denom;
        switch(numobj.type)
        {
        case INT:
            return fraction_to_float != numobj.i;

        case FLOAT:
            return fraction_to_float != numobj.f;

        case FRACTION:
            fraction_to_float2 = (float) numobj.ff.numer / numobj.ff.denom;
            return fraction_to_float != fraction_to_float2;
        }
        break;
    default:
        break;
    }



}
