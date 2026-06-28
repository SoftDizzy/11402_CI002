#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B

int main()
{
    int n, q;
    int cases = 1;

    while (cin >> n >> q)
    {
        if (n == 0 && q == 0)
        {
            break;
        }

        vector<int> marbles(n);

        for (int i = 0; i < n; i++)
        {
            cin >> marbles[i];
        }

        sort(marbles.begin(), marbles.end());

        cout << "CASE# " << cases << ":" << endl;

        while (q--)
        {
            int x;
            cin >> x;

            auto it = lower_bound(marbles.begin(), marbles.end(), x);

            if (it != marbles.end() && *it == x)
            {
                cout << x << " found at " << (it - marbles.begin() + 1) << endl;
            }
            else
            {
                cout << x << " not found" << endl;
            }
        }

        cases++;
    }

    return 0;
}