#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A Bonus

bool canFill(vector<int>& vessels, int m, int capacity)
{
    int containerCount = 1;
    int currentSum = 0;

    for (int i = 0; i < vessels.size(); i++)
    {
        if (vessels[i] > capacity)
        {
            return false;
        }

        if (currentSum + vessels[i] <= capacity)
        {
            currentSum += vessels[i];
        }
        else
        {
            containerCount++;
            currentSum = vessels[i];
        }
    }

    return containerCount <= m;
}

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        vector<int> vessels(n);

        int low = 0;
        int high = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> vessels[i];

            low = max(low, vessels[i]);
            high += vessels[i];
        }

        int answer = high;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (canFill(vessels, m, mid))
            {
                answer = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        cout << answer << endl;
    }

    return 0;
}