#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// A Bonus

int main()
{
    int n, s;

    while (cin >> n >> s)
    {
        vector<int> v(n);

        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        int left = 0;
        int sum = 0;
        int answer = INT_MAX;

        for (int right = 0; right < n; right++)
        {
            sum += v[right];

            while (sum >= s)
            {
                int length = right - left + 1;

                if (length < answer)
                {
                    answer = length;
                }

                sum -= v[left];
                left++;
            }
        }

        if (answer == INT_MAX)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << answer << endl;
        }
    }

    return 0;
}