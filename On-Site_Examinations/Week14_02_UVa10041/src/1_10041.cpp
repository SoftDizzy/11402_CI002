#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


// A

int main()
{
    int testbase;
    cin >> testbase;
    while ( testbase-- )
    {
        int n;
        cin >> n;
        vector <int> v;
        
        for ( int i = 0; i < n; i++ )
        {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }

        sort(v.begin(),v.end());
        int mid = v[ n / 2 ];
        int sum = 0;

        for ( int j = 0; j < n; j++ )
        {
            sum += abs ( v[j] - mid );
        }

        cout << sum << endl;
    }
}