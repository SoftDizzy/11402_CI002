#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

// B

int main()
{
    int C, S;
    int cases = 1;

    while (cin >> C >> S)
    {
        vector<int> mass(2 * C, 0);

        int totalMass = 0;

        for (int i = 0; i < S; i++)
        {
            cin >> mass[i];
            totalMass += mass[i];
        }

        sort(mass.begin(), mass.end());

        double average = (double)totalMass / C;
        double imbalance = 0.0;

        cout << "Set #" << cases << endl;

        for (int i = 0; i < C; i++)
        {
            int left = mass[i];
            int right = mass[2 * C - 1 - i];

            cout << " " << i << ":";

            if (left != 0)
            {
                cout << " " << left;
            }

            if (right != 0)
            {
                cout << " " << right;
            }

            cout << endl;

            int chamberMass = left + right;
            imbalance += abs(chamberMass - average);
        }

        cout << fixed << setprecision(5);
        cout << "IMBALANCE = " << imbalance << endl << endl;

        cases++;
    }

    return 0;
}