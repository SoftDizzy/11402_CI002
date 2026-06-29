#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B Bonus

const long long LIMIT = 1000000000000000000LL;

long long maxNodes(int height)
{
    if (height <= 0)
    {
        return 0;
    }

    long long nodes = 1;

    for (int i = 0; i < height; i++)
    {
        nodes *= 2;

        if (nodes > LIMIT)
        {
            return LIMIT;
        }
    }

    return nodes - 1;
}

int minHeight(int nodes)
{
    int height = 0;

    while (maxNodes(height) < nodes)
    {
        height++;
    }

    return height;
}

void buildBST(int startValue, int nodes, int height, vector<int> &answer)
{
    if (nodes <= 0)
    {
        return;
    }

    long long maxLeftNodes = maxNodes(height - 1);

    int leftNodes = min((long long)(nodes - height), maxLeftNodes);
    int rightNodes = nodes - 1 - leftNodes;

    int root = startValue + leftNodes;

    answer.push_back(root);

    int leftHeight = minHeight(leftNodes);

    buildBST(startValue, leftNodes, leftHeight, answer);
    buildBST(root + 1, rightNodes, height - 1, answer);
}

int main()
{
    int N, H;
    int cases = 1;

    while (cin >> N >> H)
    {
        cout << "Case " << cases << ":";

        if (H > N || maxNodes(H) < N)
        {
            cout << " Impossible." << endl;
        }
        else
        {
            vector<int> answer;

            buildBST(1, N, H, answer);

            for (int i = 0; i < answer.size(); i++)
            {
                cout << " " << answer[i];
            }

            cout << endl;
        }

        cases++;
    }

    return 0;
}