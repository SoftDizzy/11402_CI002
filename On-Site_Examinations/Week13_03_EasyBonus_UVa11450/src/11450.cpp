#include <iostream>
#include <vector>

using namespace std;

// A Bonus

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int money, garmentCount;
        cin >> money >> garmentCount;

        vector<vector<int>> garments(garmentCount);

        for (int i = 0; i < garmentCount; i++)
        {
            int modelCount;
            cin >> modelCount;

            for (int j = 0; j < modelCount; j++)
            {
                int price;
                cin >> price;
                garments[i].push_back(price);
            }
        }

        vector<vector<bool>> dp(garmentCount + 1, vector<bool>(money + 1, false));

        dp[0][0] = true;

        for (int i = 0; i < garmentCount; i++)
        {
            for (int spent = 0; spent <= money; spent++)
            {
                if (dp[i][spent])
                {
                    for (int j = 0; j < garments[i].size(); j++)
                    {
                        int newSpent = spent + garments[i][j];

                        if (newSpent <= money)
                        {
                            dp[i + 1][newSpent] = true;
                        }
                    }
                }
            }
        }

        int answer = -1;

        for (int spent = money; spent >= 0; spent--)
        {
            if (dp[garmentCount][spent])
            {
                answer = spent;
                break;
            }
        }

        if (answer == -1)
        {
            cout << "no solution" << endl;
        }
        else
        {
            cout << answer << endl;
        }
    }

    return 0;
}