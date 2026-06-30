#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// B Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        map<vector<int>, int> countMap;

        for (int i = 0; i < n; i++)
        {
            vector<int> courses(5);

            for (int j = 0; j < 5; j++)
            {
                cin >> courses[j];
            }

            sort(courses.begin(), courses.end());

            countMap[courses]++;
        }

        int maxCount = 0;

        for (map<vector<int>, int>::iterator it = countMap.begin(); it != countMap.end(); it++)
        {
            if (it->second > maxCount)
            {
                maxCount = it->second;
            }
        }

        int answer = 0;

        for (map<vector<int>, int>::iterator it = countMap.begin(); it != countMap.end(); it++)
        {
            if (it->second == maxCount)
            {
                answer += it->second;
            }
        }

        cout << answer << endl;
    }

    return 0;
}