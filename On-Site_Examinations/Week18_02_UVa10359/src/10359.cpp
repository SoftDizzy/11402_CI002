#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// B

string addString(string a, string b)
{
    string result = "";
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;

        if (i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }

        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    vector<string> dp(251);

    dp[0] = "1";
    dp[1] = "1";

    for (int i = 2; i <= 250; i++)
    {
        string twoTimes = addString(dp[i - 2], dp[i - 2]);
        dp[i] = addString(dp[i - 1], twoTimes);
    }

    int n;

    while (cin >> n)
    {
        cout << dp[n] << endl;
    }

    return 0;
}