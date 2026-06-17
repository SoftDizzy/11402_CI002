#include <iostream>


using namespace std;

// A

int main()
{
    int a,b;
    while ( cin >> a >> b )
    {
        if ( a == 0 && b == 0 )  break;

        int c = 0;
        int k = 0;
        
        while ( a > 0 || b > 0 )
        {
            int sum = 0;
            sum = a % 10 + b % 10 + k;
            if ( sum >= 10 )
            {
                c++;
                k = 1;
            }
            else 
            {
                k = 0;
            }
            a /= 10;
            b /= 10;
        }

        if ( c == 0 )
        {
            cout << "No carry operation." << endl;
        }
        else if ( c == 1 )
        {
            cout << "1 carry operation." << endl;
        }
        else
        {
           cout << c << " carry operations." << endl;
        }
    }
}