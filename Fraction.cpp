#include "Fraction.h"

Fraction Fraction::operator + (const Fraction &f) const
{
    return Fraction( numer*f.denom + f.numer*denom, denom*f.denom );
}

Fraction Fraction::operator + (int a) const
{
    return Fraction( numer+denom*a, denom );
}

Fraction Fraction::operator - (const Fraction &f)const
{
    return Fraction( numer*f.denom - f.numer*denom, denom*f.denom );
}

Fraction Fraction::operator - (int a)const
{
    return Fraction( numer-a*denom, denom );
}


Fraction Fraction::operator * (int a)const
{
    return Fraction( numer*a, denom ); 
}

Fraction Fraction::operator * (const Fraction &f)const
{
    return Fraction( numer*f.numer, denom*f.denom );
}

Fraction Fraction::operator / (const Fraction &f)const
{
    return Fraction( numer*f.denom , denom*f.numer );
}

Fraction Fraction::operator / (int a) const
{
    return Fraction(numer,denom*a);
}

ostream &operator << ( ostream &out, Fraction &f )
{
    out << f.numer << "/" << f.denom;
    return out;
}


