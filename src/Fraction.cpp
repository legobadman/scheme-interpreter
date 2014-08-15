#include "Fraction.h"

Fraction Fraction::operator + (Fraction &f)
{
    return Fraction( numer*f.denom + f.numer*denom, denom*f.denom );
}

Fraction Fraction::operator + (int a)
{
    return Fraction( numer+denom*a, denom );
}

Fraction Fraction::operator - (Fraction &f)
{
    return Fraction( numer*f.denom - f.numer*denom, denom*f.denom );
}

Fraction Fraction::operator - (int a)
{
    return Fraction( numer-a*denom, denom );
}


Fraction Fraction::operator * (int a)
{
    return Fraction( numer*a, denom ); 
}

Fraction Fraction::operator * (Fraction &f)
{
    return Fraction( numer*f.denom, denom*f.denom );
}

Fraction Fraction::operator / (Fraction &f)
{
    return Fraction( numer*f.denom , denom*f.numer );
}

Fraction Fraction::operator / (int a)
{
    return Fraction(numer,denom*a);
}

ostream &operator << ( ostream &out, Fraction &f )
{
    out << f.numer << "/" << f.denom << endl;
    return out;
}

Fraction operator+ (int a,Fraction f)
{
    return Fraction( f.numer+f.denom*a, f.denom );
}

Fraction operator- (int a,Fraction f)
{
    return Fraction( f.denom*a-f.numer, f.denom );
}

Fraction operator* (int a,Fraction f)
{
    return Fraction( f.numer * a, f.denom );
}

Fraction operator/ (int a,Fraction f)
{
    return Fraction( f.numer, f.denom*a );
}

