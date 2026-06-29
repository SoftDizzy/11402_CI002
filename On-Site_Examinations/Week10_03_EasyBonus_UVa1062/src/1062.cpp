#include <iostream>
#include <string>
#include <vector>

using namespace std;

// A Bonus

int main()
{
    string s;
    int cases = 1;

    while (cin >> s)
    {
        if (s == "end")
        {
            break;
        }

        vector<char> stacks;

        for (int i = 0; i < s.size(); i++)
        {
            char container = s[i];
            bool placed = false;

            for (int j = 0; j < stacks.size(); j++)
            {
                if (stacks[j] >= container)
                {
                    stacks[j] = container;
                    placed = true;
                    break;
                }
            }

            if (!placed)
            {
                stacks.push_back(container);
            }
        }

        cout << "Case " << cases << ": " << stacks.size() << endl;
        cases++;
    }

    return 0;
}