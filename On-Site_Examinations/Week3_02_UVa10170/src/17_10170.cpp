#include <iostream>

using namespace std;

//  B

int main()
{
    long long s,d;

    while ( cin >> s >> d )
    {
        long long sum = 0;
        long long ans = s;

        while ( sum < d )
        {
            sum += ans;
            ans++;
        }

        cout << ans - 1 << endl;
    }
}