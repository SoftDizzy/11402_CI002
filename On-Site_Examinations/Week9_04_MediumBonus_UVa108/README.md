# UVa 108 - Maximum Sum

## 1. Problem Information

Platform: UVa
Problem ID: 108
Problem Title: Maximum Sum
Problem Link: https://onlinejudge.org/external/1/108.pdf
Week: 9
Date: 2026/04/21
Theme: Prefix sums / difference arrays
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/108.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個 `n x n` 的矩陣，矩陣裡面有正數也可能有負數。我要找出一個連續的子矩形，讓這個子矩形裡面的數字總和最大。

### What is the input?

* 輸入有多組資料。
* 每組資料先輸入一個整數 `n`。
* 接著輸入 `n x n` 個整數，代表整個矩陣。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每組資料，輸出最大子矩形總和。
* 每組答案輸出一行。

### What are the main rules or constraints?

* 子矩形必須是連續的範圍。
* 矩陣裡可能有負數。
* 答案可能也是負數，所以不能一開始把最大值設成 0。
* 要找的是所有可能子矩形裡面總和最大的那一個。

### What is the core task you must solve?

* 把 2D 矩陣問題轉成多次 1D 最大連續子陣列問題，找出最大子矩形總和。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果直接枚舉所有子矩形，再把裡面的數字加起來，會很麻煩也比較慢。
* 後來想到可以固定子矩形的上邊界和下邊界。
* 固定上下邊界後，每一欄在這個範圍內的總和就可以壓成一個一維陣列。
* 這樣問題就變成在一維陣列裡找最大連續區間和。

### Final Strategy

* 先讀入整個 `n x n` 矩陣。
* 用 `top` 枚舉子矩形的上邊界。
* 對每個 `top`，建立 `colSum`，一開始全部是 0。
* 再用 `bottom` 從 `top` 往下枚舉下邊界。
* 每增加一個 `bottom`，就把那一列的值加進 `colSum`。
* 此時 `colSum[col]` 就代表從 `top` 到 `bottom` 這幾列，在第 `col` 欄的總和。
* 接著在 `colSum` 上做 Kadane’s Algorithm，找最大連續子陣列和。
* 每次找到比較大的值就更新 `best`。

What edge cases did you consider?

* 矩陣裡全部都是負數
* 最大子矩形可能只有一個元素
* 最大子矩形可能包含多列多欄
* 輸入有多組資料，要讀到 EOF
* `best` 要設成 `INT_MIN`，不能設成 0

## 4. Pseudocode

```text
START
1. While input has n:
2.     Read the n x n matrix.
3.     Set best = INT_MIN.
4.     For top from 0 to n - 1:
5.         Create colSum array and set all values to 0.
6.         For bottom from top to n - 1:
7.             Add row bottom into colSum.
8.             Use Kadane's Algorithm on colSum.
9.             Update best if a larger sum is found.
10.    Print best.
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
#include <climits>

using namespace std;

// B Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        vector<vector<int>> a(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
            }
        }

        int best = INT_MIN;

        for (int top = 0; top < n; top++)
        {
            vector<int> colSum(n, 0);

            for (int bottom = top; bottom < n; bottom++)
            {
                for (int col = 0; col < n; col++)
                {
                    colSum[col] += a[bottom][col];
                }

                int current = 0;

                for (int col = 0; col < n; col++)
                {
                    if (current < 0)
                    {
                        current = colSum[col];
                    }
                    else
                    {
                        current += colSum[col];
                    }

                    if (current > best)
                    {
                        best = current;
                    }
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
```

Why it works:

* 程式用 `top` 和 `bottom` 固定子矩形的上下邊界。
* 固定上下邊界後，把每一欄的總和存進 `colSum`。
* 這樣就可以把 2D 的子矩形問題變成 1D 的最大連續子陣列問題。
* Kadane’s Algorithm 可以找出目前 `colSum` 裡最大的連續區間和。
* `best` 一開始設成 `INT_MIN`，所以即使矩陣全是負數，也可以找到正確答案。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code     | Correct Code                       |
| --------------- | ------------- | ---------------------------------- |
| Logic           | 可能直接枚舉所有子矩形。  | 固定上下邊界，轉成 1D 最大連續子陣列。              |
| Edge Cases      | 可能全負數時輸出 0。   | `best` 使用 `INT_MIN`，可以處理全負數。       |
| Output Handling | 可能只處理一筆輸入。    | 使用 `while (cin >> n)` 讀到 EOF。      |
| Other           | 可能沒有正確累積欄位總和。 | 使用 `colSum` 保存 top 到 bottom 的每欄總和。 |

### Reflection

這題最重要的是固定上下邊界後，用 `colSum` 代表每一欄的總和。
接著就可以用 Kadane’s Algorithm 找最大連續區間。

