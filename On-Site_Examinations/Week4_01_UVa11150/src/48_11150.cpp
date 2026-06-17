#include <iostream>

using namespace std;


//      A

int main()
{
    int n;

    while (cin >> n)
    {
        int total = n;
        int empty = n;

        while (empty >= 3)
        {
            int newCola = empty / 3;
            total += newCola;

            empty = empty % 3 + newCola;
        }

        if (empty == 2)
        {
            total++;
        }

        cout << total << endl;
    }

    return 0;
}