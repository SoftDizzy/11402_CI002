#include <iostream>

using namespace std;

// A Bonus

int main()
{
    unsigned long long dp[65][65] = {0};

    for (int back = 0; back <= 60; back++)
    {
        dp[0][back] = 1;
        dp[1][back] = 1;
    }

    for (int n = 2; n <= 60; n++)
    {
        for (int back = 0; back <= 60; back++)
        {
            unsigned long long sum = 0;

            for (int k = 1; k <= back; k++)
            {
                if (n - k < 0)
                {
                    sum += 1;
                }
                else
                {
                    sum += dp[n - k][back];
                }
            }

            dp[n][back] = sum + 1;
        }
    }

    int n, back;
    int cases = 1;

    while (cin >> n >> back)
    {
        if (n > 60)
        {
            break;
        }

        if (n < 0)
        {
            n = 0;
        }

        cout << "Case " << cases << ": " << dp[n][back] << endl;
        cases++;
    }

    return 0;
}