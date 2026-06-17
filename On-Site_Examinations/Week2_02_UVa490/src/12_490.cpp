#include <iostream>
#include <vector>

using namespace std;

//  B

int main()
{
    string s[110];
    int n = 0;
    int max_len = 0;

    while ( getline( cin,s[n]) )
    {
        if ( s[n].size() > max_len )
        {
            max_len = s[n].size();
        }
        n++;
    }
    for ( int i = 0; i < max_len; i++ )
    {
        for ( int j = n - 1; j >= 0; j-- )
        {
            if ( i >= s[j].size() )
            {
                cout << " ";
            }
            else
            {
                cout << s[j][i];
            }
        }
        cout << endl;
    }
    return 0;
}