# UVa 12149 - Feynman

## 1. Problem Information

Platform: UVa
Problem ID: 12149
Problem Title: Feynman
Problem Link: https://onlinejudge.org/external/121/12149.pdf
Week: 3
Date: 2026/03/10
Theme: Math + corner cases
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12149.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個整數 `n`，代表有一個 `n x n` 的大正方形。我要算出這個大正方形裡面總共有幾個不同大小的正方形。

### What is the input?

* 輸入有很多個整數 `n`。
* 當 `n = 0` 時，代表輸入結束，不需要輸出。

### What is the expected output?

* 對每一個 `n`，輸出 `n x n` 裡面所有正方形的總數。

### What are the main rules or constraints?

* `1 x 1` 的正方形有很多個。
* `2 x 2`、`3 x 3` 這些不同大小的正方形也都要算進去。
* 輸入 `0` 時要停止。
* 每筆答案輸出一行。

### What is the core task you must solve?

* 核心任務是計算：

```text
1^2 + 2^2 + 3^2 + ... + n^2
```

這個總和就是 `n x n` 正方形裡面所有小正方形的數量。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到題目，我原本以為要真的去數每個格子裡面的正方形。
* 後來發現其實有規律，因為不同大小的正方形數量可以用平方和表示。
* 例如 `n = 3` 時，答案是 `1^2 + 2^2 + 3^2 = 14`。

### Final Strategy

* 每次讀入一個 `n`。
* 如果 `n == 0`，就結束程式。
* 設定 `sum = 0`。
* 從 `1` 加到 `n`，每次把 `i * i` 加進 `sum`。
* 最後輸出 `sum`。

What edge cases did you consider?

* 輸入 `0` 時不能輸出
* `n = 1` 時答案是 1
* 有多筆輸入，要一直讀到 0
* 每筆輸出都要換行
* 不能只算 `n * n`，因為還要包含其他大小的正方形

## 4. Pseudocode


```text
START
1. While input has an integer n:
2.     If n == 0:
3.         Stop the program.
4.     Set sum = 0.
5.     For i from 1 to n:
6.         Add i * i to sum.
7.     Print sum.
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
    int n;

    while ( cin >> n )
    {
        if ( n == 0 )
        {
            break;
        }

        int sum = 0;

        for ( int i = 1; i <= n; i++ )
        {
            sum += i * i;
        }

        cout << sum << endl;
    }

    return 0;
}
```

Why it works:

* 程式可以一直讀取 `n`，直到遇到 `0` 才停止。
* 對每個 `n`，用迴圈加總 `1^2` 到 `n^2`。
* 這個平方和剛好就是所有不同大小正方形的總數。
* 每筆答案都有獨立輸出一行，符合題目格式。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code                   |
| --------------- | ---------------- | ------------------------------ |
| Logic           | 可能只算 `n * n`。    | 使用平方和 `1^2 + 2^2 + ... + n^2`。 |
| Edge Cases      | 可能沒有處理 `n == 0`。 | 遇到 `0` 就停止，不輸出。                |
| Output Handling | 可能只處理一筆資料。       | 可以處理多筆輸入，每筆輸出一行。               |
| Other           | 可能沒有看出題目的數學規律。   | 用迴圈把每個大小的正方形數量加起來。             |

### Reflection

這題主要是在找規律。
一開始如果只想到 `n * n`，就會只算到最小的正方形，答案會少很多。

我學到這種數格子的題目，可以先用小數字畫圖找規律。
像 `n = 1, 2, 3` 先算一次，就比較容易發現答案是平方和。

