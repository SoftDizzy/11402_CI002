# UVa 10446 - The Marriage Interview :-)

## 1. Problem Information

Platform: UVa
Problem ID: 10446
Problem Title: The Marriage Interview :-)
Problem Link: https://onlinejudge.org/external/104/10446.pdf
Week: 18
Date: Not specified
Theme: Dynamic Programming / Memoization
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10446.cpp`

## 2. Problem Statement in My Own Words

* 這題是在計算一個遞迴函式會被呼叫幾次。
* 函式有兩個參數：`n` 和 `back`。
* 當 `n` 是 base case 時，呼叫次數是 1。
* 其他情況會往前呼叫 `back` 個狀態，並且目前這次呼叫本身也要算 1 次。

### What is the input?

* 輸入有多組資料。
* 每組資料有兩個整數：

  * `n`
  * `back`
* 當 `n > 60` 時，代表輸入結束。

### What is the expected output?

* 每組資料輸出：

```text 
Case x: answer
```

其中 `answer` 是對應的函式呼叫次數。

### What are the main rules or constraints?

* `n = 0` 和 `n = 1` 時，答案都是 1。
* 對其他 `n`，答案會由前面 `back` 個狀態加總而來。
* 目前這次呼叫本身也要算一次，所以最後要再加 1。
* 答案可能很大，所以使用 `unsigned long long`。
* 可以先用 DP 預先算好所有可能的答案。

### What is the core task you must solve?

* 用 DP 記錄 `dp[n][back]`，避免重複遞迴計算，並快速輸出每組答案。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果直接照題目遞迴去算，會有很多重複呼叫。
* 因為題目要的是呼叫次數，不是實際函式值，所以可以把每個狀態先算好。
* 狀態跟 `n` 和 `back` 都有關，所以需要二維 DP。

### Final Strategy

* 建立二維陣列：

```text 
dp[n][back]
```

代表 `trib(n, back)` 的呼叫次數。

* 先設定 base case：

```text 
dp[0][back] = 1
dp[1][back] = 1
```

* 對於 `n >= 2`，轉移式為：

```text 
dp[n][back] = 1 + dp[n - 1][back] + dp[n - 2][back] + ... + dp[n - back][back]
```

* 前面的 `1` 代表目前這次 function call。
* 如果 `n - k < 0`，就當成 base case，也加 1。
* 先預先算好 `n` 和 `back` 到 60 的答案。
* 之後每次讀入 `n` 和 `back`，直接輸出 `dp[n][back]`。

What edge cases did you consider?

* `n = 0`
* `n = 1`
* `n - k < 0` 時要當成 base case
* `n > 60` 時要停止輸入
* 答案可能很大，所以使用 `unsigned long long`
* 每組輸出都要有 Case 編號

## 4. Pseudocode

```text 
START
1. Create dp[65][65], initialized to 0.
2. For back from 0 to 60:
3.     dp[0][back] = 1.
4.     dp[1][back] = 1.
5. For n from 2 to 60:
6.     For back from 0 to 60:
7.         Set sum = 0.
8.         For k from 1 to back:
9.             If n - k < 0:
10.                sum += 1.
11.            Else:
12.                sum += dp[n - k][back].
13.        dp[n][back] = sum + 1.
14. Set cases = 1.
15. While input has n and back:
16.     If n > 60:
17.         Stop the program.
18.     If n < 0:
19.         Set n = 0.
20.     Print "Case cases: dp[n][back]".
21.     cases++.
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

// A Bonus

int main()
{
    unsigned long long dp[65][65] = {0};

    for (int back = 0; back <= 60; back++)
    {
        dp[0][back] = 1;
        dp[1][back] = 1;
    }

    for (int n = 2; n <= 60; n++)
    {
        for (int back = 0; back <= 60; back++)
        {
            unsigned long long sum = 0;

            for (int k = 1; k <= back; k++)
            {
                if (n - k < 0)
                {
                    sum += 1;
                }
                else
                {
                    sum += dp[n - k][back];
                }
            }

            dp[n][back] = sum + 1;
        }
    }

    int n, back;
    int cases = 1;

    while (cin >> n >> back)
    {
        if (n > 60)
        {
            break;
        }

        if (n < 0)
        {
            n = 0;
        }

        cout << "Case " << cases << ": " << dp[n][back] << endl;
        cases++;
    }

    return 0;
}
```

Why it works:

* 程式使用 `dp[n][back]` 記錄每個狀態的呼叫次數。
* `dp[0][back]` 和 `dp[1][back]` 都是 base case，所以設成 1。
* 對於其他 `n`，會把前 `back` 個狀態的呼叫次數加起來。
* `sum + 1` 中的 1 代表目前這一次呼叫本身。
* 所有答案先預先算好，所以讀入測資時可以直接查表輸出。
* 使用 `unsigned long long` 可以處理較大的答案範圍。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                |
| --------------- | ------------------ | --------------------------- |
| Logic           | 可能直接遞迴計算。          | 使用 DP 預先計算所有狀態。             |
| Edge Cases      | 可能沒處理 `n - k < 0`。 | 小於 0 時當成 base case，加 1。     |
| Output Handling | 可能 Case 編號格式錯。     | 使用 `Case x: answer`。        |
| Other           | 可能忘記目前呼叫也要算一次。     | 每個非 base case 都會 `sum + 1`。 |

### Reflection

所以每個狀態除了加上子問題的呼叫次數，也要記得加上目前這次呼叫本身。

我覺得這題容易錯在 base case 和 `n - k < 0` 的處理。
如果直接遞迴，會重複算很多次；改成 DP 後，邏輯比較清楚，也能很快輸出答案。

