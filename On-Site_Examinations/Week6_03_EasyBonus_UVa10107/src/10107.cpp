#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A Bonus

int main()
{
    vector<int> v;
    int x;

    while (cin >> x)
    {
        v.push_back(x);
        sort(v.begin(), v.end());

        int n = v.size();

        if (n % 2 == 1)
        {
            cout << v[n / 2] << endl;
        }
        else
        {
            cout << (v[n / 2 - 1] + v[n / 2]) / 2 << endl;
        }
    }

    return 0;
}