#include <iostream>
#include <cctype>
using namespace std;

//  A

int main()
{
    string s1,s2;


    while ( getline(cin,s1) && getline(cin,s2))
    {
        int c1[26]={0};
        int c2[26]={0};
        for ( int i = 0; i < s1.size(); i++ )
        {
            int index1 = s1[i] - 'a';
            c1[index1]++;
        }
        for ( int i = 0; i < s2.size(); i++ )
        {
            int index2 = s2[i] - 'a';
            c2[index2]++;
        }
        for ( int i = 0; i < 26; i++ )
        {
            int same = min( c1[i],c2[i] );
            for ( int j = 0; j < same; j++ )
            {
                char c = i + 'a';
                cout << c;
            }
        }
        cout << endl;
    }
    return 0;
}