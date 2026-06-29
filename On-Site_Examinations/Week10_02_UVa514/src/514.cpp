#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// B

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        while (true)
        {
            vector<int> target(n);

            cin >> target[0];

            if (target[0] == 0)
            {
                cout << endl;
                break;
            }

            for (int i = 1; i < n; i++)
            {
                cin >> target[i];
            }

            stack<int> station;
            int currentTrain = 1;
            int index = 0;

            while (currentTrain <= n)
            {
                station.push(currentTrain);
                currentTrain++;

                while (!station.empty() && station.top() == target[index])
                {
                    station.pop();
                    index++;
                }
            }

            if (index == n)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}