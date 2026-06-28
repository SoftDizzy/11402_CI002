#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// B Bonus

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int m, n;
        cin >> m >> n;

        vector<int> add(m);
        vector<int> query(n);

        for (int i = 0; i < m; i++)
        {
            cin >> add[i];
        }

        for (int i = 0; i < n; i++)
        {
            cin >> query[i];
        }

        priority_queue<int> lower;
        priority_queue<int, vector<int>, greater<int>> upper;

        int addIndex = 0;

        for (int i = 0; i < n; i++)
        {
            int needAdd = query[i];

            while (addIndex < needAdd)
            {
                int x = add[addIndex];

                if (lower.empty() || x <= lower.top())
                {
                    lower.push(x);
                }
                else
                {
                    upper.push(x);
                }

                addIndex++;
            }

            int needSize = i + 1;

            while ((int)lower.size() > needSize)
            {
                upper.push(lower.top());
                lower.pop();
            }

            while ((int)lower.size() < needSize)
            {
                lower.push(upper.top());
                upper.pop();
            }

            while (!upper.empty() && !lower.empty() && lower.top() > upper.top())
            {
                int a = lower.top();
                int b = upper.top();

                lower.pop();
                upper.pop();

                lower.push(b);
                upper.push(a);
            }

            cout << lower.top() << endl;
        }

        if (testCase)
        {
            cout << endl;
        }
    }

    return 0;
}