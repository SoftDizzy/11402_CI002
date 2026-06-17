#include <iostream>
#include <string>


using namespace std;

// A

int main()
{
    string s;
    bool a = true;
    while ( getline ( cin , s ) )
    {

        for ( int i = 0; i < s.size(); i++ )
        {
            char c = s[i];
            if ( c == '"')
            {
                if ( a == true )
                {
                    cout << "``";
                    a = false;
                }
                else
                {
                    cout << "''";
                    a = true;
                }
            }
            else
                cout << c;

        }
        cout << endl;
    }
    return 0;
}