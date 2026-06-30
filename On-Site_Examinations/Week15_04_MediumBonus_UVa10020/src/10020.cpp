#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B Bonus

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 0; cases < testCase; cases++)
    {
        int M;
        cin >> M;

        vector<pair<int, int>> segments;

        while (true)
        {
            int L, R;
            cin >> L >> R;

            if (L == 0 && R == 0)
            {
                break;
            }

            segments.push_back(make_pair(L, R));
        }

        sort(segments.begin(), segments.end());

        vector<pair<int, int>> answer;

        int current = 0;
        int index = 0;
        bool possible = true;

        while (current < M)
        {
            int bestRight = current;
            pair<int, int> bestSegment;

            while (index < segments.size() && segments[index].first <= current)
            {
                if (segments[index].second > bestRight)
                {
                    bestRight = segments[index].second;
                    bestSegment = segments[index];
                }

                index++;
            }

            if (bestRight == current)
            {
                possible = false;
                break;
            }

            answer.push_back(bestSegment);
            current = bestRight;
        }

        if (cases > 0)
        {
            cout << endl;
        }

        if (!possible)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << answer.size() << endl;

            for (int i = 0; i < answer.size(); i++)
            {
                cout << answer[i].first << " " << answer[i].second << endl;
            }
        }
    }

    return 0;
}