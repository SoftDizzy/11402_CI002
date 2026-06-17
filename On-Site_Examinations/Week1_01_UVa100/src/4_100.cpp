#include <iostream>
#include <algorithm>

using namespace std;

// A

int main()
{
    int i,j;
    while ( cin >> i >> j )
    {

        int start = min( i , j );
        int end = max( i , j );

        int max_length = 0;
        for ( int i = start; i <= end; i++ )
        {
            int n = i;
            int length = 1;
            while ( n != 1 )
            {
                if ( n % 2 == 1 )
                {
                    n = 3 * n + 1;
                    length++;
                }
                else
                {
                    n = n / 2;
                    length++;
                }
            }
            if ( length > max_length )
            {
                max_length = length;
            }
        }
        cout << i << " " << j << " " << max_length << endl;
    }
}