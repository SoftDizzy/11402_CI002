#include <iostream>
#include <vector>

using namespace std;

// A Bonus

int main()
{
    int S, B;

    while (cin >> S >> B)
    {
        if (S == 0 && B == 0)
        {
            break;
        }

        vector<int> left(S + 2);
        vector<int> right(S + 2);

        for (int i = 1; i <= S; i++)
        {
            left[i] = i - 1;
            right[i] = i + 1;
        }

        right[S] = 0;

        for (int i = 0; i < B; i++)
        {
            int L, R;
            cin >> L >> R;

            int leftBuddy = left[L];
            int rightBuddy = right[R];

            if (leftBuddy == 0)
            {
                cout << "*";
            }
            else
            {
                cout << leftBuddy;
            }

            cout << " ";

            if (rightBuddy == 0)
            {
                cout << "*";
            }
            else
            {
                cout << rightBuddy;
            }

            cout << endl;

            if (leftBuddy != 0)
            {
                right[leftBuddy] = rightBuddy;
            }

            if (rightBuddy != 0)
            {
                left[rightBuddy] = leftBuddy;
            }
        }

        cout << "-" << endl;
    }

    return 0;
}