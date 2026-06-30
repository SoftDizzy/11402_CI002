# UVa 11286 - Conformity

## 1. Problem Information

Platform: UVa
Problem ID: 11286
Problem Title: Conformity
Problem Link: https://onlinejudge.org/external/112/11286.pdf
Week: 14
Date: 2026/05/26
Theme: Sorting / Map / Frequency Counting
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11286.cpp`

## 2. Problem Statement in My Own Words

* 這題會給很多學生選的課程組合，每個學生會選 5 門課。
* 我要找出最熱門的課程組合有多少人選。
* 如果有多個組合並列最熱門，要把這些組合的人數全部加起來。

### What is the input?

* 輸入有多組資料。
* 每組先輸入一個整數 `n`，代表有幾個學生。
* 接著每個學生會輸入 5 個課程編號。
* 如果 `n = 0`，代表輸入結束。

### What is the expected output?

* 對每組資料輸出一個整數。
* 這個整數代表選擇最熱門課程組合的學生總數。

### What are the main rules or constraints?

* 每個學生選 5 門課。
* 課程輸入順序不重要。
* 例如：

```text 
100 200 300 400 500
500 400 300 200 100
```

這兩個要視為同一種組合。

* 所以每個學生的 5 門課要先排序。
* 如果有多個組合出現次數都等於最高次數，要把它們的人數加總。

### What is the core task you must solve?

* 把每個學生的課程組合排序後，用 map 統計每種組合出現幾次，最後加總最熱門組合的人數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果直接把 5 個課程當成一組來比，會有順序問題。
* 同樣的 5 門課可能用不同順序輸入，但實際上應該算同一種組合。
* 所以每組課程要先排序，讓相同組合變成一樣的形式。
* 接著就可以用 `map<vector<int>, int>` 來統計。

### Final Strategy

* 每次讀入 `n`。
* 如果 `n == 0`，就結束。
* 建立 `map<vector<int>, int> countMap`。
* 對每個學生：

  * 讀入 5 個課程編號。
  * 把這 5 個課程放入 `vector<int>`。
  * 將 vector 排序。
  * 用排序後的 vector 當 key，讓 `countMap[courses]++`。
* 統計完成後，先找出最大出現次數 `maxCount`。
* 再掃一次 map，把所有出現次數等於 `maxCount` 的組合人數加到 `answer`。
* 最後輸出 `answer`。

What edge cases did you consider?

* `n = 0` 時要停止
* 課程組合輸入順序不同但內容相同
* 只有一種最熱門組合
* 多種組合並列最熱門
* 每組資料都要重新建立 map
* 不能只輸出 `maxCount`，要輸出所有最熱門組合的人數總和

## 4. Pseudocode

```text 
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Create an empty map countMap.
5.     Repeat n times:
6.         Read 5 course numbers into courses.
7.         Sort courses.
8.         countMap[courses]++.
9.     Set maxCount = 0.
10.    For each item in countMap:
11.        If item count > maxCount:
12.            maxCount = item count.
13.    Set answer = 0.
14.    For each item in countMap:
15.        If item count == maxCount:
16.            answer += item count.
17.    Print answer.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

### Correct Code

```cpp 
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
```

Why it works:

* 每個學生的 5 門課先排序後，相同課程組合就會變成相同的 vector。
* `map<vector<int>, int>` 可以把整個課程組合當作 key，並統計出現次數。
* 第一輪掃 map 可以找出最高出現次數。
* 第二輪掃 map 可以把所有並列最高的組合人數加起來。
* 最後輸出的不是單一組合的人數，而是所有最熱門組合的人數總和，符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                   |
| --------------- | ----------------- | ------------------------------ |
| Logic           | 可能直接用輸入順序當組合。     | 先排序課程，讓相同組合格式一致。               |
| Edge Cases      | 可能忽略並列最熱門組合。      | 把所有 `count == maxCount` 的人數加總。 |
| Output Handling | 可能只輸出 `maxCount`。 | 輸出所有最熱門組合的總人數。                 |
| Other           | 可能每組資料沒有清空統計。     | 每次重新建立 `countMap`。             |

### Reflection

這題是 sorting 加 map 的題目。
我覺得最重要的是先把每個人的 5 門課排序，因為課程順序不代表不同組合。

這題也提醒我，題目問的不是「最高次數是多少」，而是「有多少學生選了最熱門的組合」。
如果有很多組合並列第一，就要全部加起來。

