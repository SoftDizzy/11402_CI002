#include <iostream>

using namespace std;

// B

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int D, I;
        cin >> D >> I;

        int node = 1;

        for (int level = 1; level < D; level++)
        {
            if (I % 2 == 1)
            {
                node = node * 2;
                I = (I + 1) / 2;
            }
            else
            {
                node = node * 2 + 1;
                I = I / 2;
            }
        }

        cout << node << endl;
    }

    return 0;
}