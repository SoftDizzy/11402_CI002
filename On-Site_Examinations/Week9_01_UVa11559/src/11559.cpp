#include <iostream>
#include <algorithm>

using namespace std;

// A

int main()
{
    int n, b, h, w;

    while (cin >> n >> b >> h >> w)
    {
        int best = b + 1;

        for (int i = 0; i < h; i++)
        {
            int price;
            cin >> price;

            bool enoughBeds = false;

            for (int j = 0; j < w; j++)
            {
                int beds;
                cin >> beds;

                if (beds >= n)
                {
                    enoughBeds = true;
                }
            }

            int cost = n * price;

            if (enoughBeds && cost <= b)
            {
                best = min(best, cost);
            }
        }

        if (best <= b)
        {
            cout << best << endl;
        }
        else
        {
            cout << "stay home" << endl;
        }
    }

    return 0;
}