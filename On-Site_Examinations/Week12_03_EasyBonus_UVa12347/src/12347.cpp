#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// A Bonus

vector<int> preorder;
int indexNow = 0;

void printPostorder(long long low, long long high)
{
    if (indexNow >= preorder.size())
    {
        return;
    }

    int root = preorder[indexNow];

    if (root <= low || root >= high)
    {
        return;
    }

    indexNow++;

    printPostorder(low, root);
    printPostorder(root, high);

    cout << root << endl;
}

int main()
{
    int x;

    while (cin >> x)
    {
        preorder.push_back(x);
    }

    printPostorder(LLONG_MIN, LLONG_MAX);

    return 0;
}