#include <iostream>
#include <set>

using namespace std;

// B Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        multiset<int> bills;
        long long total = 0;

        for (int day = 0; day < n; day++)
        {
            int k;
            cin >> k;

            for (int i = 0; i < k; i++)
            {
                int value;
                cin >> value;
                bills.insert(value);
            }

            auto low = bills.begin();
            auto high = prev(bills.end());

            total += *high - *low;

            bills.erase(low);
            bills.erase(high);
        }

        cout << total << endl;
    }

    return 0;
}