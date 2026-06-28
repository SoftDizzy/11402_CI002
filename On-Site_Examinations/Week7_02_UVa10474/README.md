# UVa 10474 - Where is the Marble?

## 1. Problem Information

Platform: UVa
Problem ID: 10474
Problem Title: Where is the Marble?
Problem Link: https://onlinejudge.org/external/104/10474.pdf
Week: 7
Date: 2026/04/07
Theme: Binary search
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10474.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一堆 marble 的數字，接著有多個查詢。我要找出查詢的數字有沒有出現在 marble 裡，如果有，要輸出它排序後第一次出現的位置。

### What is the input?

* 輸入有多組資料。
* 每組資料先給兩個整數 `n` 和 `q`。

  * `n` 是 marble 的數量。
  * `q` 是查詢數量。
* 接著輸入 `n` 個 marble 數字。
* 再輸入 `q` 個查詢數字。
* 當 `n = 0` 且 `q = 0` 時，代表輸入結束。

### What is the expected output?

* 每組資料要先輸出：

```text
CASE# x:
```

* 如果查詢的數字有找到，輸出：

```text
number found at position
```

* 如果沒有找到，輸出：

```text
number not found
```

* 位置是排序後的第幾個，從 1 開始算。

### What are the main rules or constraints?

* marble 要先排序。
* 查詢時要找的是目標數字第一次出現的位置。
* 如果有重複數字，要輸出最前面的那個位置。
* 輸出格式要注意是 `CASE#`，不是 `Case`。
* 輸入遇到 `0 0` 要停止。

### What is the core task you must solve?

* 排序 marble 後，使用二分搜尋找到查詢數字第一次出現的位置。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以用線性搜尋，每次查詢都從頭找一次。
* 但這題主題是 binary search，而且查詢可能很多，所以更適合先排序再查找。
* 因為題目要找第一次出現的位置，所以可以用 `lower_bound`。

### Final Strategy

* 先讀入 `n` 和 `q`。
* 如果是 `0 0` 就結束。
* 用 `vector<int>` 存 marble 數字。
* 把 marble 排序。
* 每次查詢一個數字 `x`。
* 使用 `lower_bound` 找第一個大於等於 `x` 的位置。
* 如果這個位置沒有超出範圍，而且值等於 `x`，代表有找到。
* 輸出位置時要加 1，因為題目位置從 1 開始。
* 如果找不到，就輸出 `not found`。

What edge cases did you consider?

* 查詢數字不存在
* 查詢數字重複出現在 marble 裡
* 要輸出第一次出現的位置
* 輸入 `0 0` 時停止
* Case 編號要從 1 開始
* 輸出格式的 `CASE#` 和冒號不能錯

## 4. Pseudocode

```text
START
1. Set cases = 1.
2. While input has n and q:
3.     If n == 0 and q == 0:
4.         Stop the program.
5.     Read n marble numbers into vector.
6.     Sort the vector.
7.     Print "CASE# cases:".
8.     Repeat q times:
9.         Read query number x.
10.        Use lower_bound to find first position >= x.
11.        If position is valid and value equals x:
12.            Print x found at position + 1.
13.        Else:
14.            Print x not found.
15.    Increase cases by 1.
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

using namespace std;

// B

int main()
{
    int n, q;
    int cases = 1;

    while (cin >> n >> q)
    {
        if (n == 0 && q == 0)
        {
            break;
        }

        vector<int> marbles(n);

        for (int i = 0; i < n; i++)
        {
            cin >> marbles[i];
        }

        sort(marbles.begin(), marbles.end());

        cout << "CASE# " << cases << ":" << endl;

        while (q--)
        {
            int x;
            cin >> x;

            auto it = lower_bound(marbles.begin(), marbles.end(), x);

            if (it != marbles.end() && *it == x)
            {
                cout << x << " found at " << (it - marbles.begin() + 1) << endl;
            }
            else
            {
                cout << x << " not found" << endl;
            }
        }

        cases++;
    }

    return 0;
}
```

Why it works:

* 程式先把 marble 數字排序，這樣才能使用二分搜尋。
* `lower_bound` 會找到第一個大於等於查詢數字的位置。
* 如果該位置的值剛好等於查詢數字，就代表有找到，而且這個位置也是第一次出現的位置。
* 輸出時用 `it - marbles.begin() + 1`，把 0-based index 轉成題目要的 1-based position。
* 如果找不到，就輸出 `not found`。
* 程式會一直處理到輸入 `0 0` 為止。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                |
| --------------- | ------------------ | --------------------------- |
| Logic           | 可能每次都用線性搜尋。        | 先排序，再用 `lower_bound` 搜尋。    |
| Edge Cases      | 可能遇到重複數字時位置錯。      | `lower_bound` 可以找到第一次出現的位置。 |
| Output Handling | 可能位置從 0 開始輸出。      | 輸出時加 1，符合題目位置從 1 開始。        |
| Other           | 可能忘記結束條件或 Case 格式。 | 遇到 `0 0` 停止，並輸出 `CASE# x:`。 |

### Reflection

這題是 binary search 的基本應用。
我學到如果題目要找排序後第一次出現的位置，可以使用 `lower_bound`，比自己手寫搜尋更簡單。

下次遇到查詢很多筆的題目，我會先想能不能排序後用二分搜尋，避免每次都從頭找。
