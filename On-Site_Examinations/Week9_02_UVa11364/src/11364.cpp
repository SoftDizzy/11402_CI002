#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int n;
        cin >> n;

        vector<int> shops(n);

        for (int i = 0; i < n; i++)
        {
            cin >> shops[i];
        }

        sort(shops.begin(), shops.end());

        int distance = (shops[n - 1] - shops[0]) * 2;

        cout << distance << endl;
    }

    return 0;
}