#include <iostream>
#include <algorithm>

using namespace std;

//  A

int main()
{
    int testbase;
    cin >> testbase;
    
    int count = 1;
    while ( testbase-- )
    {
        int a,b;
        cin >> a >> b;
        int start = min( a, b );
        int end = max( a, b );

        int sum = 0;

        for ( int i = start; i <= end; i++ )
        {
            if ( i % 2 == 1 )
            {
                sum += i;
            }
        }


        cout << "Case " << count  << ": " << sum << endl;
        count++;
    }
    return 0;
}