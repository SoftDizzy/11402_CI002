#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// B Bonus

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 1; cases <= testCase; cases++)
    {
        int n, d;
        cin >> n >> d;

        vector<int> stones;

        stones.push_back(0);
        stones.push_back(0);

        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;

            char type = s[0];
            int position = stoi(s.substr(2));

            if (type == 'B')
            {
                stones.push_back(position);
                stones.push_back(position);
            }
            else
            {
                stones.push_back(position);
            }
        }

        stones.push_back(d);
        stones.push_back(d);

        int answer = 0;

        for (int i = 2; i < stones.size(); i++)
        {
            answer = max(answer, stones[i] - stones[i - 2]);
        }

        cout << "Case " << cases << ": " << answer << endl;
    }

    return 0;
}