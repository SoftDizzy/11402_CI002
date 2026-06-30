#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A

int main()
{
    int n, d, r;

    while (cin >> n >> d >> r)
    {
        if (n == 0 && d == 0 && r == 0)
        {
            break;
        }

        vector<int> morning(n);
        vector<int> evening(n);

        for (int i = 0; i < n; i++)
        {
            cin >> morning[i];
        }

        for (int i = 0; i < n; i++)
        {
            cin >> evening[i];
        }

        sort(morning.begin(), morning.end());
        sort(evening.begin(), evening.end(), greater<int>());

        int overtime = 0;

        for (int i = 0; i < n; i++)
        {
            int total = morning[i] + evening[i];

            if (total > d)
            {
                overtime += total - d;
            }
        }

        cout << overtime * r << endl;
    }

    return 0;
}