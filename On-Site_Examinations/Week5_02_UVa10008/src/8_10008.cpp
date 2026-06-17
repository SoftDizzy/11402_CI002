#include <iostream>
#include <cctype>

using namespace std;

// B

int main()
{
    int n;
    cin >> n;
    cin.ignore();
    int a[26] = {0};
    int max_c = 0;
    while ( n-- )
    {
        string line;
        getline( cin , line );

        for ( int i = 0; i < line.size(); i++ )
        {
            char c = line[i];
            if ( isalpha(c) )
            {
                c = toupper(c);
                int index = c - 'A';
                a[index]++;

                if ( a[index] > max_c )
                {
                    max_c = a[index];
                }
            }

        }

    }

    for ( int i = max_c; i > 0; i-- )
    {
        for ( int j = 0; j < 26; j++ )
        {
            if ( a[j] == i )
            {
                char z = 'A' + j;
                cout << z << " " << i << endl;
            }
        }
    }
    return 0;
}