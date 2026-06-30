# UVa 900 - Brick Wall Patterns

## 1. Problem Information

Platform: UVa
Problem ID: 900
Problem Title: Brick Wall Patterns
Problem Link: https://onlinejudge.org/external/9/900.pdf
Week: 18
Date: Not specified
Theme: Dynamic Programming / Fibonacci
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/900.cpp`

## 2. Problem Statement in My Own Words

* 這題要計算寬度為 `n` 的牆有幾種排磚方式。
* 可以把它想成每次可以放寬度 1 的磚，或是放寬度 2 的磚。
* 問題會一直給不同的 `n`，直到輸入 `0` 結束。

### What is the input?

* 輸入有多組資料。
* 每組資料是一個整數 `n`。
* 如果 `n = 0`，代表輸入結束。

### What is the expected output?

* 對每個 `n`，輸出寬度為 `n` 的牆有幾種排法。
* 每組答案輸出一行。

### What are the main rules or constraints?

* `n = 0` 時不輸出答案，直接結束。
* 這題的排法數量符合 Fibonacci 類型。
* 寬度 `n` 的排法可以從寬度 `n - 1` 和 `n - 2` 推出。
* 因為答案可能比較大，所以使用 `long long`。

### What is the core task you must solve?

* 用 DP 預先算出每個寬度的排法數，再根據輸入輸出答案。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以用遞迴想，但如果每次都重新算會重複很多狀態。
* 這題其實就是 Fibonacci 類型的 DP。
* 只要先把 `dp[0]` 到 `dp[50]` 算好，後面查詢時直接輸出即可。

### Final Strategy

* 定義：

```text 
dp[n] = 寬度 n 的牆有幾種排法
```

* 初始值：

```text 
dp[0] = 1
dp[1] = 1
```

* 對於寬度 `n`，最後一段可能有兩種情況：

  * 放一個寬度 1 的磚，前面剩下 `n - 1`
  * 放一個寬度 2 的磚，前面剩下 `n - 2`
* 所以轉移式是：

```text 
dp[n] = dp[n - 1] + dp[n - 2]
```

* 先用迴圈算到 `dp[50]`。
* 之後一直讀入 `n`。
* 如果 `n == 0`，結束。
* 否則輸出 `dp[n]`。

What edge cases did you consider?

* `n = 0` 時要停止
* `n = 1` 時答案是 1
* 多組輸入要一直處理
* 不要每次都重新計算 DP
* 答案可能超過 int，所以使用 `long long`

## 4. Pseudocode

```text 
START
1. Create dp array.
2. Set dp[0] = 1.
3. Set dp[1] = 1.
4. For i from 2 to 50:
5.     dp[i] = dp[i - 1] + dp[i - 2].
6. While input has n:
7.     If n == 0:
8.         Stop the program.
9.     Print dp[n].
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

using namespace std;

// A

int main()
{
    long long dp[51];

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= 50; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        cout << dp[n] << endl;
    }

    return 0;
}
```

Why it works:

* `dp[n]` 表示寬度為 `n` 的牆有幾種排法。
* 寬度 `n` 可以從 `n - 1` 加上一塊寬度 1 的磚，或從 `n - 2` 加上一塊寬度 2 的磚得到。
* 所以 `dp[n] = dp[n - 1] + dp[n - 2]`。
* 程式先把所有可能的答案預先算好，後面每次輸入 `n` 都可以直接輸出。
* 遇到 `0` 時會正確停止。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code        |
| --------------- | ---------------- | ------------------- |
| Logic           | 可能用遞迴重複計算。       | 使用 DP 預先計算答案。       |
| Edge Cases      | 可能 `n = 0` 時還輸出。 | 遇到 `0` 直接結束。        |
| Output Handling | 可能每次重新算。         | 查表後直接輸出 `dp[n]`。    |
| Other           | 可能型別不夠大。         | 使用 `long long` 存答案。 |

### Reflection

只要最後放寬度 1 的磚，就會剩下 `n - 1`；如果最後放寬度 2 的磚，就會剩下 `n - 2`。
所以就是 `dp[n] = dp[n - 1] + dp[n - 2]`。

