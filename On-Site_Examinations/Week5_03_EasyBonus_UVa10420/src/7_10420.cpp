#include <iostream>
#include <map>

using namespace std;

// A 

int main()
{
    int testbase;
    cin >> testbase;
    map < string , int > list;
    while ( testbase-- )
    {
        string country;
        cin >> country;

        string people;
        getline ( cin , people );

        list[country]++;
        
    }

    for ( auto i : list )
    {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}