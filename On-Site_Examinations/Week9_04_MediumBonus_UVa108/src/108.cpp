#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// B Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        vector<vector<int>> a(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
            }
        }

        int best = INT_MIN;

        for (int top = 0; top < n; top++)
        {
            vector<int> colSum(n, 0);

            for (int bottom = top; bottom < n; bottom++)
            {
                for (int col = 0; col < n; col++)
                {
                    colSum[col] += a[bottom][col];
                }

                int current = 0;

                for (int col = 0; col < n; col++)
                {
                    if (current < 0)
                    {
                        current = colSum[col];
                    }
                    else
                    {
                        current += colSum[col];
                    }

                    if (current > best)
                    {
                        best = current;
                    }
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}