#include "../Fraction.h"
using namespace std;



int main()
{
    int x = 3;
    Fraction f1(3);
    Fraction f2(2,3);
    Fraction f3;

    f3 = f1+f2;
    cout << f1 << " + " << f2 << " = " << f3 << endl;
    
    f3 = f1*f2;
    cout << f1 << " * " << f2 << " = " << f3 << endl;

    Fraction f4 = f1/f2;
    cout << f1 << " / " << f2 << " = " << f4 << endl;

    f4 = 3 + f3;
    cout << f3 << " / " << 3 << " = " << f4 << endl;

}
