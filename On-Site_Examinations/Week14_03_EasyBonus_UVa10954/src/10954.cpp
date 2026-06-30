#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

// A Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            pq.push(x);
        }

        long long cost = 0;

        while (pq.size() > 1)
        {
            int a = pq.top();
            pq.pop();

            int b = pq.top();
            pq.pop();

            int sum = a + b;
            cost += sum;

            pq.push(sum);
        }

        cout << cost << endl;
    }

    return 0;
}