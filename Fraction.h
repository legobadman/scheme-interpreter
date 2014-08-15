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

    Fraction(const Fraction& f)
    {
        numer = f.numer;
        denom = f.denom;
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
    Fraction operator + ( const Fraction& )const;
    Fraction operator + ( int )const;

    Fraction operator * ( const Fraction& )const;
    Fraction operator * ( int )const;

    Fraction operator / ( const Fraction& )const;
    Fraction operator / ( int )const;

    Fraction operator - ( const Fraction& )const;
    Fraction operator - ( int )const;

    int numer;
    int denom;
};


ostream &operator << ( ostream&, Fraction& ); 

#endif
