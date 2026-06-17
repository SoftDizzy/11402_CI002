#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 統計每一行字串中，每個字元出現幾次，
// 並依照題目規則輸出 ASCII 值和出現次數。

//      B

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.second != b.second)
    {
        // 出現次數不同時，次數少的排前面
        return a.second < b.second;
    }

    // 出現次數相同時，ASCII 值大的排前面
    return a.first > b.first;
}

int main()
{
    string s;

    // 題目要求每組輸出之間要空一行，
    // 但第一組前面不能先空行，所以用 firstCase 控制。
    bool firstCase = true;

    while (getline(cin, s))
    {
        if (firstCase == false)
        {
            cout << endl;
        }

        firstCase = false;

        // 建立 ASCII 統計表，freq[i] 代表 ASCII 值 i 出現幾次
        int freq[128] = {0};

        for (int i = 0; i < s.size(); i++)
        {
            int ascii = s[i];   // 取得目前字元的 ASCII 值
            freq[ascii]++;      // 對應 ASCII 的出現次數加一
        }

        vector<pair<int, int>> v;

        for (int ascii = 0; ascii < 128; ascii++)
        {
            if (freq[ascii] > 0)
            {
                // 把有出現過的字元，以 {ASCII值, 出現次數} 存進 vector
                v.push_back({ascii, freq[ascii]});
            }
        }

        // 依照題目規則排序：
        // 1. 出現次數由小到大
        // 2. 次數相同時，ASCII 值由大到小
        sort(v.begin(), v.end(), cmp);

        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i].first << " " << v[i].second << endl;
        }
    }

    return 0;
}