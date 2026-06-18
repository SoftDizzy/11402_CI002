# UVa 10170 - The Hotel with Infinite Rooms

## 1. Problem Information

Platform: UVa
Problem ID: 10170
Problem Title: The Hotel with Infinite Rooms
Problem Link: https://onlinejudge.org/external/101/10170.pdf
Week: 3
Date: 2026/03/10
Theme: Math + corner cases
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/17_10170.cpp`

## 2. Problem Statement in My Own Words

* 這題會給起始房間人數 `s` 和目標天數或累積人數 `d`，我要找出累積總和第一次大於等於 `d` 時，當天住進來的人數是多少。

### What is the input?

* 輸入有多組資料。
* 每一組有兩個整數 `s` 和 `d`。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每一組輸入，輸出一個整數。
* 這個整數代表累積總和達到或超過 `d` 時，當下的數字是多少。

### What are the main rules or constraints?

* 一開始從 `s` 開始加。
* 每次加完後，下一個數字會增加 1。
* 要一直累加到總和 `sum >= d`。
* 因為數字可能很大，所以使用 `long long` 比較安全。

### What is the core task you must solve?

* 核心任務是從 `s` 開始連續累加 `s, s+1, s+2...`，找到總和第一次達到或超過 `d` 時的最後一個數字。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始的想法是直接照題意模擬。
* 從 `s` 開始累加，每加一次就把下一個數字加 1。
* 只要累積總和還沒到 `d`，就繼續加。

### Final Strategy

* 先讀入 `s` 和 `d`。
* 設定 `sum = 0`，用來記錄目前累積總和。
* 設定 `ans = s`，代表目前要加的數字。
* 當 `sum < d` 時：

  * 把 `ans` 加到 `sum`
  * 然後 `ans++`
* 因為最後一次迴圈結束時 `ans` 已經多加 1，所以輸出 `ans - 1`。

What edge cases did you consider?

* 有多組輸入，要讀到 EOF
* `s` 和 `d` 可能很大，所以用 `long long`
* 如果第一次加 `s` 就已經超過 `d`，答案就是 `s`
* 最後輸出時要注意 `ans` 已經先加 1，所以要輸出 `ans - 1`

## 4. Pseudocode


```text
START
1. While input has s and d:
2.     Set sum = 0.
3.     Set ans = s.
4.     While sum < d:
5.         Add ans to sum.
6.         Increase ans by 1.
7.     Print ans - 1.
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

//  B

int main()
{
    long long s,d;

    while ( cin >> s >> d )
    {
        long long sum = 0;
        long long ans = s;

        while ( sum < d )
        {
            sum += ans;
            ans++;
        }

        cout << ans - 1 << endl;
    }
}
```

Why it works:

* 程式可以一直讀取 `s` 和 `d`，直到 EOF。
* `sum` 用來記錄目前累積的總和。
* `ans` 從 `s` 開始，每次加完後就加 1，剛好符合題目連續累加的規則。
* 當 `sum >= d` 時停止，代表已經找到答案。
* 因為 `ans` 在最後一次加完後又多加了 1，所以輸出 `ans - 1`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code                                     |
| --------------- | --------------- | ------------------------------------------------ |
| Logic           | 可能沒有照連續累加的方式模擬。 | 從 `s` 開始一路加到總和達到 `d`。                            |
| Edge Cases      | 可能沒處理大數或 EOF。   | 使用 `long long`，並用 `while (cin >> s >> d)` 讀多組資料。 |
| Output Handling | 可能直接輸出 `ans`。   | 輸出 `ans - 1`，避免多加一次。                             |
| Other           | 可能迴圈條件寫錯。       | 用 `sum < d` 控制，達到目標就停止。                          |

### Reflection

這題比較容易錯的是最後輸出。
因為 `ans` 在迴圈裡加完後會先 `ans++`，所以真正答案是 `ans - 1`。

下次遇到這種累加題，我會特別注意變數是在加之前還是加之後改變，避免最後多輸出一個數字。
