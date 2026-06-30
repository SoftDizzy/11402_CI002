#include <iostream>
#include <string>

using namespace std;

// A

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 1; cases <= testCase; cases++)
    {
        int n;
        string field;

        cin >> n >> field;

        int scarecrow = 0;

        for (int i = 0; i < n; )
        {
            if (field[i] == '.')
            {
                scarecrow++;
                i += 3;
            }
            else
            {
                i++;
            }
        }

        cout << "Case " << cases << ": " << scarecrow << endl;
    }

    return 0;
}