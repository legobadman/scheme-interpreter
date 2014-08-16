#include "Fraction.h"

#define abs(a) ((a)>=0)?(a):-a

static int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}


Fraction::Fraction(const Fraction& f)
{
    int n = abs(f.numer);
    int d = abs(f.denom);

    int gcd_num;

    if( n>d )
        gcd_num = gcd(n,d);
    else
        gcd_num = gcd(d,n);

    numer = f.numer / gcd_num;
    denom = f.denom / gcd_num;
}

Fraction::Fraction(int n, int d)
{
    int absn = abs(n);
    int absd = abs(d);

    int gcd_num;

    if( absn>absd )
        gcd_num = gcd(absn,absd);
    else
        gcd_num = gcd(absd,absn);

    numer = n / gcd_num;
    denom = d / gcd_num;
}

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
    if( f.numer % f.denom == 0)
        out << f.numer / f.denom;
    else
        out << f.numer << "/" << f.denom;
    return out;
}



Fraction operator+ (int a, const Fraction &f)
{
    return Fraction( a*f.denom + f.numer, f.denom ); 
}

Fraction operator* (int a, const Fraction &f)
{
    return Fraction( a*f.numer, f.denom );
}

Fraction operator- (int a, const Fraction &f)
{
    return Fraction( a*f.denom-f.numer, f.denom );
}

Fraction operator/ (int a, const Fraction &f)
{
    return Fraction( a * f.denom, f.numer ); 
}
