# UVa 10062 - Tell me the frequencies!

## 1. Problem Information

Platform: UVa
Problem ID: 10062
Problem Title: Tell me the frequencies!
Problem Link: https://onlinejudge.org/external/100/10062.pdf
Week: 6
Date: 2026/03/31
Theme: Median / order statistics
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/41_10062.cpp`

## 2. Problem Statement in My Own Words

* 這題會給很多行字串，我要統計每一行裡面每個字元出現幾次，最後依照題目規則輸出 ASCII 值和出現次數。

### What is the input?

* 輸入有多行字串。
* 每一行都要單獨處理。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每一行字串，輸出該行中每個有出現過的字元。
* 輸出格式是：

```text
ASCII_value frequency
```

* 不同測資輸出之間要空一行。
* 第一組測資前面不能先空行。

### What are the main rules or constraints?

* 要統計每個字元的 ASCII 值和出現次數。
* 排序時，出現次數少的要排前面。
* 如果出現次數一樣，ASCII 值大的要排前面。
* 每一行都要重新統計，不能和前一行混在一起。
* 要用 `getline` 讀整行，因為輸入可能包含空白。

### What is the core task you must solve?

* 對每一行字串做字元頻率統計，然後照「次數小到大、ASCII 大到小」排序輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想到可以用一個陣列統計 ASCII 字元出現次數。
* 因為 ASCII 值範圍不大，所以用 `freq[128]` 就可以處理。
* 比較麻煩的是排序規則不是一般字母順序，而是要先看出現次數，再看 ASCII 值。

### Final Strategy

* 每次用 `getline` 讀一行字串。
* 用 `freq[128]` 統計每個 ASCII 字元出現幾次。
* 把有出現過的字元存成 `pair<int, int>` 放進 vector。

  * `first` 存 ASCII 值。
  * `second` 存出現次數。
* 寫一個比較函式 `cmp`：

  * 如果次數不同，次數少的排前面。
  * 如果次數相同，ASCII 值大的排前面。
* 排序後依序輸出。
* 用 `firstCase` 控制不同測資之間的空行，避免第一組前面多印空行。

What edge cases did you consider?

* 輸入行中有空白字元
* 每一行都要重新統計
* 多組輸出中間要空一行
* 第一組輸出前不能有空行
* 次數相同時，ASCII 值大的要先輸出

## 4. Pseudocode

```text
START
1. Set firstCase = true.
2. While input has a line s:
3.     If firstCase is false:
4.         Print a blank line.
5.     Set firstCase = false.
6.     Create freq[128] and set all values to 0.
7.     For each character in s:
8.         Convert it to ASCII value.
9.         Add 1 to freq[ASCII value].
10.    Create an empty vector.
11.    For each ASCII value from 0 to 127:
12.        If freq[ASCII value] > 0:
13.            Store {ASCII value, frequency} into vector.
14.    Sort vector by frequency ascending.
15.    If frequency is the same, sort by ASCII value descending.
16.    Print each ASCII value and frequency.
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
```

Why it works:

* 程式用 `getline` 讀每一整行，所以空白字元也會被保留下來。
* 每一行都重新建立 `freq[128]`，不會和前一行的統計混在一起。
* `vector<pair<int, int>>` 用來存有出現過的 ASCII 值和出現次數。
* `cmp` 函式處理排序規則：次數少的先輸出，次數相同時 ASCII 值大的先輸出。
* `firstCase` 可以避免第一組前面多印空行，同時讓不同測資之間有空白行。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code            | Correct Code               |
| --------------- | -------------------- | -------------------------- |
| Logic           | 可能沒有正確統計每個 ASCII 字元。 | 使用 `freq[128]` 統計每一行的字元次數。 |
| Edge Cases      | 可能忽略空白字元或多行輸入。       | 使用 `getline`，每一行獨立處理。      |
| Output Handling | 可能空行位置錯誤。            | 用 `firstCase` 控制測資之間的空行。   |
| Other           | 排序規則可能寫錯。            | 用 `cmp` 實作次數升序、ASCII 降序。   |

### Reflection

這題最容易錯的是排序規則。
它不是 ASCII 小的先，也不是次數大的先，而是出現次數少的先；如果次數一樣，ASCII 值大的先。

這題讓我更熟悉 `pair`、`vector` 和自訂排序函式。

