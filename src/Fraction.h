#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>

using namespace std;


class Fraction
{
public:
    Fraction()
    {
        numer=0;
        denom=1;
    }
    Fraction(int x)
    {
        numer=x;
        denom=1;
    }

    Fraction(int n,int d)
    {
        numer = n;
        denom = d;
    } 
    Fraction operator + ( Fraction& );
    Fraction operator + ( int );

    Fraction operator * ( Fraction& );
    Fraction operator * ( int );

    Fraction operator / ( Fraction& );
    Fraction operator / ( int );

    Fraction operator - ( Fraction& );
    Fraction operator - ( int );

    int numer;
    int denom;
};


Fraction operator+ (int a, Fraction f);

ostream &operator << ( ostream&, Fraction& ); 

#endif
