#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <iostream>
#include <cstdlib>
#include "Fraction.h"

/* support INT, FLOAT, FRACTION */
enum DataType{ INT=1, FLOAT, FRACTION };

//class Fraction;

class Number
{
public:
    Number(){}
    Number( std::string str );
    Number( int i ); 
    Number( float f );
    Number( int numer, int denom );
    Number( Fraction ff );

    int getInteger()const{ return i; }
    float getFloat()const{ return f; }
    DataType getType()const{ return type; }

    friend std::ostream &operator << ( std::ostream &out, Number num );
    
    Number operator + (const Number& );
    Number operator - (const Number& );
    Number operator * (const Number& );
    Number operator / (const Number& );
    
    Number operator = (int a){ i=a; type=INT; }
    Number operator = (float b){ f=b; type=FLOAT; }

    bool operator < (const Number& );
    bool operator <= (const Number& );
    bool operator > (const Number& );
    bool operator >= (const Number& );
    bool operator == (const Number& );

private:
    float   f;
    int     i;
    Fraction ff; 
    DataType type;
};


#endif
