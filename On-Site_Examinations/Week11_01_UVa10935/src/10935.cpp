#include <iostream>
#include <queue>

using namespace std;

// A

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        queue<int> cards;

        for (int i = 1; i <= n; i++)
        {
            cards.push(i);
        }

        cout << "Discarded cards:";

        bool first = true;

        while (cards.size() > 1)
        {
            int discarded = cards.front();
            cards.pop();

            if (first)
            {
                cout << " " << discarded;
                first = false;
            }
            else
            {
                cout << ", " << discarded;
            }

            int moved = cards.front();
            cards.pop();
            cards.push(moved);
        }

        cout << endl;
        cout << "Remaining card: " << cards.front() << endl;
    }

    return 0;
}