# UVa 10359 - Tiling

## 1. Problem Information

Platform: UVa
Problem ID: 10359
Problem Title: Tiling
Problem Link: https://onlinejudge.org/external/103/10359.pdf
Week: 18
Date: Not specified
Theme: Dynamic Programming / Big Integer
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10359.cpp`

## 2. Problem Statement in My Own Words

* 這題要計算寬度為 `n` 的區域有幾種 tiling 方法。
* 因為 `n` 可以到 250，答案會非常大，不能只用一般整數型別。
* 所以這題除了 DP，也需要用字串處理大數加法。

### What is the input?

* 輸入有多組資料。
* 每組資料是一個整數 `n`。
* 要一直讀到 EOF 為止。

### What is the expected output?

* 對每個 `n`，輸出對應的 tiling 方法數。
* 每組答案輸出一行。

### What are the main rules or constraints?

* 這題的答案會比 `long long` 還大。
* 需要用 Big Integer 的方式處理。
* C++ 沒有內建 Big Integer，所以用 `string` 自己做加法。
* DP 轉移式是：

```text 
dp[n] = dp[n - 1] + 2 * dp[n - 2]
```

### What is the core task you must solve?

* 用 DP 算出 tiling 數量，並用字串大數加法避免數字溢位。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始這題看起來像前一題 Brick Wall Patterns，但轉移式不一樣。
* 如果只用 `long long`，很快就會超過範圍。
* 所以需要先把 DP 想好，再處理大數相加。

### Final Strategy

* 用 `vector<string> dp(251)` 存答案。
* `dp[i]` 用字串表示寬度 `i` 的 tiling 方法數。
* 初始值：

```text 
dp[0] = "1"
dp[1] = "1"
```

* 對 `i >= 2`：

```text 
dp[i] = dp[i - 1] + 2 * dp[i - 2]
```

* 因為都是字串，所以寫一個 `addString(a, b)` 函式來做大數加法。
* `2 * dp[i - 2]` 可以用：

```text 
addString(dp[i - 2], dp[i - 2])
```

* 先預先算好 `dp[0]` 到 `dp[250]`。
* 之後每次讀入 `n`，直接輸出 `dp[n]`。

What edge cases did you consider?

* `n = 0`
* `n = 1`
* `n` 很大時答案超過 long long
* 多組輸入要讀到 EOF
* 大數加法要處理 carry
* 加法結果最後要反轉回正常順序

## 4. Pseudocode

```text 
START
1. Define addString(a, b):
2.     Start from the last digit of a and b.
3.     Add digits with carry.
4.     Store each result digit.
5.     Reverse the result string.
6.     Return result.

7. Create dp array of string with size 251.
8. Set dp[0] = "1".
9. Set dp[1] = "1".
10. For i from 2 to 250:
11.     twoTimes = addString(dp[i - 2], dp[i - 2]).
12.     dp[i] = addString(dp[i - 1], twoTimes).
13. While input has n:
14.     Print dp[n].
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

// B

string addString(string a, string b)
{
    string result = "";
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;

        if (i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }

        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    vector<string> dp(251);

    dp[0] = "1";
    dp[1] = "1";

    for (int i = 2; i <= 250; i++)
    {
        string twoTimes = addString(dp[i - 2], dp[i - 2]);
        dp[i] = addString(dp[i - 1], twoTimes);
    }

    int n;

    while (cin >> n)
    {
        cout << dp[n] << endl;
    }

    return 0;
}
```

Why it works:

* `dp[n]` 表示寬度為 `n` 的 tiling 方法數。
* 轉移式 `dp[n] = dp[n - 1] + 2 * dp[n - 2]` 可以正確計算每個狀態。
* 因為答案很大，所以用 `string` 存每個 DP 值。
* `addString()` 從個位數開始相加，並正確處理進位。
* 先預先算到 `250`，後面每次輸入只要直接查表輸出即可。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                            |
| --------------- | ----------------- | --------------------------------------- |
| Logic           | 可能當成普通 Fibonacci。 | 使用 `dp[n] = dp[n - 1] + 2 * dp[n - 2]`。 |
| Edge Cases      | 可能數字溢位。           | 使用 string 做 Big Integer。                |
| Output Handling | 可能每次重新計算。         | 預先算好後直接輸出。                              |
| Other           | 可能沒有處理 carry。     | `addString()` 會完整處理大數加法。                |

### Reflection

我覺得最重要的是先看出正確轉移式，再處理資料型別不夠大的問題。

因為 C++ 沒有內建 Big Integer，所以用 string 自己做加法。
這也讓我練習到從字串尾端開始加、處理 carry、最後再 reverse 的大數加法寫法。

