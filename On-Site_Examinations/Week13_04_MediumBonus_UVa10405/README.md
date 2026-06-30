# UVa 10405 - Longest Common Subsequence

## 1. Problem Information

Platform: UVa
Problem ID: 10405
Problem Title: Longest Common Subsequence
Problem Link: https://onlinejudge.org/external/104/10405.pdf
Week: 13
Date: 2026/05/19
Theme: Dynamic Programming
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10405.cpp`

## 2. Problem Statement in My Own Words

* 這題會給兩個字串，要找出它們的 Longest Common Subsequence，也就是最長共同子序列的長度。

### What is the input?

* 輸入有多組資料。
* 每組資料有兩行：

  * 第一行是字串 `a`
  * 第二行是字串 `b`
* 要一直讀到 EOF 為止。

### What is the expected output?

* 對每組資料，輸出一個整數。
* 這個整數代表兩個字串的最長共同子序列長度。

### What are the main rules or constraints?

* 子序列不一定要連續。
* 但是字元的相對順序不能改變。
* 例如 `ace` 是 `abcde` 的子序列。
* 這題只需要輸出長度，不需要輸出實際的子序列內容。

### What is the core task you must solve?

* 用 DP 計算兩個字串的 LCS 長度。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果用暴力法去列出所有子序列，數量會非常多，不適合。
* LCS 是很典型的 DP 題。
* 可以用 `dp[i][j]` 表示字串 `a` 的前 `i` 個字元和字串 `b` 的前 `j` 個字元的 LCS 長度。

### Final Strategy

* 每次用 `getline` 讀入兩個字串。
* 設 `n = a.size()`，`m = b.size()`。
* 建立一個大小為 `(n + 1) x (m + 1)` 的 DP 表。
* `dp[i][j]` 代表：

```text 
a 的前 i 個字元和 b 的前 j 個字元的 LCS 長度
```

* 如果 `a[i - 1] == b[j - 1]`，代表兩個字串目前最後一個字元相同，可以一起選：

```text 
dp[i][j] = dp[i - 1][j - 1] + 1
```

* 如果兩個字元不同，就看少用 `a` 的這個字元比較好，還是少用 `b` 的這個字元比較好：

```text 
dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
```

* 最後答案就是 `dp[n][m]`。

What edge cases did you consider?

* 其中一個字串可能是空字串
* 兩個字串完全沒有共同字元
* 兩個字串完全相同
* 子序列不需要連續
* 輸入有多組資料，要讀到 EOF
* 使用 `getline`，避免空白字元被切開

## 4. Pseudocode

```text 
START
1. While getline can read string a:
2.     Read string b.
3.     n = length of a.
4.     m = length of b.
5.     Create dp table with size (n + 1) x (m + 1), initialized to 0.
6.     For i from 1 to n:
7.         For j from 1 to m:
8.             If a[i - 1] == b[j - 1]:
9.                 dp[i][j] = dp[i - 1][j - 1] + 1.
10.            Else:
11.                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]).
12.    Print dp[n][m].
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

using namespace std;

// B Bonus

int main()
{
    string a, b;

    while (getline(cin, a))
    {
        getline(cin, b);

        int n = a.size();
        int m = b.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (a[i - 1] == b[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        cout << dp[n][m] << endl;
    }

    return 0;
}
```

Why it works:

* `dp[i][j]` 清楚表示兩個字串前綴的 LCS 長度。
* 當目前兩個字元相同時，可以把這個字元加入共同子序列，所以從左上角狀態加 1。
* 當目前兩個字元不同時，只能選擇跳過其中一邊的字元，所以取上方或左方的最大值。
* DP 表從小範圍慢慢算到完整字串。
* 最後 `dp[n][m]` 就是兩個完整字串的 LCS 長度。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                          |
| --------------- | ----------------- | ------------------------------------- |
| Logic           | 可能把 LCS 當成連續字串問題。 | 使用 DP 處理不連續的子序列。                      |
| Edge Cases      | 可能無法處理空白或空字串。     | 使用 `getline` 讀整行。                     |
| Output Handling | 可能輸出實際字串或錯誤長度。    | 只輸出 LCS 長度。                           |
| Other           | 可能索引從 0 開始時寫錯。    | DP 多開一列一欄，使用 `a[i - 1]` 和 `b[j - 1]`。 |

### Reflection

我覺得最重要的是不要把 subsequence 和 substring 搞混。

Substring 要連續，但 subsequence 不用連續，只要順序一樣就可以。
所以不能只用簡單的連續比較，而是要用 DP 去記錄前綴狀態。

這題也讓我更熟悉 LCS 的基本轉移式。
之後遇到兩個字串比對、共同序列、編輯距離這類題目時，可以先想到類似的 DP 表。
