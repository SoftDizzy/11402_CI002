#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }

        vector<int> heads(n);
        vector<int> knights(m);

        for (int i = 0; i < n; i++)
        {
            cin >> heads[i];
        }

        for (int i = 0; i < m; i++)
        {
            cin >> knights[i];
        }

        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int headIndex = 0;
        int knightIndex = 0;
        long long cost = 0;

        while (headIndex < n && knightIndex < m)
        {
            if (knights[knightIndex] >= heads[headIndex])
            {
                cost += knights[knightIndex];
                headIndex++;
                knightIndex++;
            }
            else
            {
                knightIndex++;
            }
        }

        if (headIndex == n)
        {
            cout << cost << endl;
        }
        else
        {
            cout << "Loowater is doomed!" << endl;
        }
    }

    return 0;
}