#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

// A Bonus

int colorIndex(char c)
{
    if (c == 'B')
    {
        return 0;
    }
    else if (c == 'G')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int main()
{
    int bottle[3][3];

    while (cin >> bottle[0][0] >> bottle[0][1] >> bottle[0][2]
               >> bottle[1][0] >> bottle[1][1] >> bottle[1][2]
               >> bottle[2][0] >> bottle[2][1] >> bottle[2][2])
    {
        vector<string> orders;
        orders.push_back("BCG");
        orders.push_back("BGC");
        orders.push_back("CBG");
        orders.push_back("CGB");
        orders.push_back("GBC");
        orders.push_back("GCB");

        int total = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                total += bottle[i][j];
            }
        }

        string bestOrder;
        int bestMove = INT_MAX;

        for (int i = 0; i < orders.size(); i++)
        {
            string order = orders[i];

            int keep = 0;

            for (int bin = 0; bin < 3; bin++)
            {
                int color = colorIndex(order[bin]);
                keep += bottle[bin][color];
            }

            int move = total - keep;

            if (move < bestMove)
            {
                bestMove = move;
                bestOrder = order;
            }
        }

        cout << bestOrder << " " << bestMove << endl;
    }

    return 0;
}