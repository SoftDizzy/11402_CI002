# UVa 501 - Black Box

## 1. Problem Information

Platform: UVa
Problem ID: 501
Problem Title: Black Box
Problem Link: https://onlinejudge.org/external/5/501.pdf
Week: 6
Date: 2026/03/31
Theme: Median / order statistics
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/501.cpp`

## 2. Problem Statement in My Own Words

* 這題會先給一串數字，然後給幾個查詢。每次查詢會指定目前要加入前幾個數字，接著輸出目前集合中的第 k 小數字。

### What is the input?

* 第一行是測資數量。
* 每組測資會有兩個整數 `m` 和 `n`。

  * `m` 代表有幾個數字可以被加入。
  * `n` 代表有幾次查詢。
* 接著輸入 `m` 個數字。
* 再輸入 `n` 個查詢數字，代表每次查詢前總共要加入幾個數字。

### What is the expected output?

* 每次查詢都要輸出目前的第 k 小數字。
* 第一次查詢輸出第 1 小。
* 第二次查詢輸出第 2 小。
* 第三次查詢輸出第 3 小。
* 依此類推。
* 不同測資之間要空一行。

### What are the main rules or constraints?

* 數字是依照順序逐步加入，不是一開始全部加入。
* 每次 `GET` 的順序會決定要找第幾小。
* 第一次輸出第 1 小，第二次輸出第 2 小。
* 需要一直維持目前已加入數字的順序統計。
* 這題如果每次都排序也可以想，但會比較慢。

### What is the core task you must solve?

* 每次加入一些新數字後，快速找到目前集合中的第 k 小數字。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始直覺想法是用 `vector` 存目前加入的數字，每次查詢時排序後取第 k 小。
* 但是這題查詢很多，如果每次都重新排序，感覺會比較沒效率。
* 後來改用兩個 priority queue 來維持第 k 小的位置。

### Final Strategy

* 使用兩個 heap：

  * `lower`：max heap，存目前最小的 k 個數字。
  * `upper`：min heap，存剩下比較大的數字。
* 每次查詢時，先依照題目要求加入新的數字。
* 接著調整 `lower` 的大小，讓它剛好等於目前要找的第 k 小。
* 因為 `lower` 裡面存的是目前最小的 k 個數字，所以 `lower.top()` 就會是第 k 小。
* 如果兩邊 heap 的順序不對，就把元素交換，確保 `lower` 裡的數字都不會比 `upper` 裡的數字大。

What edge cases did you consider?

* 有多組測資
* 每組測資之間要空一行
* 查詢時可能一次加入多個新數字
* 第一次查詢要輸出第 1 小
* priority queue 的大小要和目前第幾次查詢對應
* 數字可能不是照大小順序加入

## 4. Pseudocode

```text
START
1. Read testCase.
2. For each test case:
3.     Read m and n.
4.     Read m numbers into add array.
5.     Read n query values.
6.     Create max heap lower.
7.     Create min heap upper.
8.     Set addIndex = 0.
9.     For each query i:
10.        Add numbers until addIndex reaches query[i].
11.        Set needSize = i + 1.
12.        Adjust lower size until it equals needSize.
13.        If lower.top is greater than upper.top, swap them.
14.        Print lower.top.
15.    Print blank line between test cases.
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
#include <queue>

using namespace std;

// B Bonus

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int m, n;
        cin >> m >> n;

        vector<int> add(m);
        vector<int> query(n);

        for (int i = 0; i < m; i++)
        {
            cin >> add[i];
        }

        for (int i = 0; i < n; i++)
        {
            cin >> query[i];
        }

        priority_queue<int> lower;
        priority_queue<int, vector<int>, greater<int>> upper;

        int addIndex = 0;

        for (int i = 0; i < n; i++)
        {
            int needAdd = query[i];

            while (addIndex < needAdd)
            {
                int x = add[addIndex];

                if (lower.empty() || x <= lower.top())
                {
                    lower.push(x);
                }
                else
                {
                    upper.push(x);
                }

                addIndex++;
            }

            int needSize = i + 1;

            while ((int)lower.size() > needSize)
            {
                upper.push(lower.top());
                lower.pop();
            }

            while ((int)lower.size() < needSize)
            {
                lower.push(upper.top());
                upper.pop();
            }

            while (!upper.empty() && !lower.empty() && lower.top() > upper.top())
            {
                int a = lower.top();
                int b = upper.top();

                lower.pop();
                upper.pop();

                lower.push(b);
                upper.push(a);
            }

            cout << lower.top() << endl;
        }

        if (testCase)
        {
            cout << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式會先把所有可加入的數字和查詢存起來。
* 每次查詢時，會把需要加入的數字加入 heap。
* `lower` 負責保存目前最小的 k 個數字。
* 每次查詢的 `k` 其實就是目前第幾次查詢，所以用 `needSize = i + 1`。
* 當 `lower` 的大小剛好是 k 時，`lower.top()` 就是第 k 小。
* `upper` 用來放剩下比較大的數字，兩個 heap 搭配可以維持目前的順序關係。
* 不同測資之間用空行分隔，符合題目格式。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                | Correct Code                |
| --------------- | ------------------------ | --------------------------- |
| Logic           | 可能每次重新排序或把題目當成一般 median。 | 使用兩個 priority queue 找第 k 小。 |
| Edge Cases      | 可能沒有照查詢加入指定數量的數字。        | 每次用 `addIndex` 加到查詢要求的位置。   |
| Output Handling | 可能忘記測資之間的空行。             | 用 `if (testCase)` 控制空行。     |
| Other           | 可能沒有維持第 k 小的位置。          | 讓 `lower.size()` 等於目前要找的 k。 |

### Reflection

它不是單純排序後輸出中位數，而是每次查詢都要輸出目前的第 k 小。

我學到如果題目一直加入資料，又要找排序後某個位置的數字，可以用 heap 來維持資料。
這裡用兩個 priority queue，把比較小的 k 個數字放在 `lower`，答案就會在 `lower.top()`。
