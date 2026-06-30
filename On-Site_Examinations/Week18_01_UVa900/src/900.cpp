#include <iostream>

using namespace std;

// A

int main()
{
    long long dp[51];

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= 50; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        cout << dp[n] << endl;
    }

    return 0;
}