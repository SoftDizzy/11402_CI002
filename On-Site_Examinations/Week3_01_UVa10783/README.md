# UVa 10783 - Odd Sum

## 1. Problem Information

Platform: UVa
Problem ID: 10783
Problem Title: Odd Sum
Problem Link: https://onlinejudge.org/external/107/10783.pdf
Week: 3
Date: 2026/03/10
Theme: Math + corner cases
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/19_10783.cpp`

## 2. Problem Statement in My Own Words

* 這題會給多組測資，每組有兩個整數 `a` 和 `b`，我要計算 `a` 到 `b` 之間所有奇數的總和。

### What is the input?

* 第一行是一個整數，代表有幾組測資。
* 接下來每組測資會有兩個整數 `a` 和 `b`。

### What is the expected output?

* 每一組測資要輸出一行：

```text
Case x: sum
```

其中 `x` 是第幾筆測資，`sum` 是範圍內奇數的總和。

### What are the main rules or constraints?

* 只需要加總奇數。
* 如果 `a` 比 `b` 大，要先把範圍調整成小到大。
* 輸出格式要有 `Case 1: ...`、`Case 2: ...` 這種編號。
* 每組測資都要獨立計算。

### What is the core task you must solve?

* 核心任務是找出兩個數字之間所有奇數，並把它們加起來。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始覺得這題可以直接用迴圈從 `a` 跑到 `b`，遇到奇數就加進 `sum`。
* 比較需要注意的是輸入的兩個數字不一定保證小到大，所以要先處理範圍。

### Final Strategy

* 先讀入測資數量 `testbase`。
* 用 `count` 記錄目前是第幾個 case。
* 每次讀入 `a` 和 `b` 後，用 `min(a, b)` 和 `max(a, b)` 找出真正的起點和終點。
* 從 `start` 跑到 `end`。
* 如果 `i % 2 == 1`，代表是奇數，就加到 `sum`。
* 最後輸出 `Case count: sum`。

What edge cases did you consider?

* `a < b` 的正常情況
* `a > b` 的反向輸入
* 範圍內沒有很多數字
* `a` 或 `b` 本身就是奇數
* Case 編號要從 1 開始
* 輸出格式的冒號和空格不能錯

## 4. Pseudocode


```text
START
1. Read testbase.
2. Set count = 1.
3. While testbase is not 0:
4.     Read a and b.
5.     Let start = smaller value of a and b.
6.     Let end = larger value of a and b.
7.     Set sum = 0.
8.     For i from start to end:
9.         If i is odd:
10.            Add i to sum.
11.    Print "Case count: sum".
12.    Add 1 to count.
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
#include <algorithm>

using namespace std;

//  A

int main()
{
    int testbase;
    cin >> testbase;
    
    int count = 1;
    while ( testbase-- )
    {
        int a,b;
        cin >> a >> b;
        int start = min( a, b );
        int end = max( a, b );

        int sum = 0;

        for ( int i = start; i <= end; i++ )
        {
            if ( i % 2 == 1 )
            {
                sum += i;
            }
        }


        cout << "Case " << count  << ": " << sum << endl;
        count++;
    }
    return 0;
}
```

Why it works:

* 程式先讀入測資數量，所以可以正確處理多筆資料。
* 使用 `min()` 和 `max()` 處理範圍，避免 `a > b` 時迴圈跑錯。
* 迴圈逐一檢查範圍內的數字，只把奇數加進 `sum`。
* `count` 用來控制 Case 編號，輸出格式符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code               |
| --------------- | ----------------- | -------------------------- |
| Logic           | 可能直接從 `a` 跑到 `b`。 | 先用 `min()` 和 `max()` 調整範圍。 |
| Edge Cases      | 可能沒處理 `a > b`。    | 反向輸入也可以正確計算。               |
| Output Handling | 可能忘記 Case 編號或格式錯。 | 輸出 `Case x: sum`。          |
| Other           | 可能沒有只加奇數。         | 用 `i % 2 == 1` 判斷奇數。       |

### Reflection

我一開始最需要注意的是 `a` 和 `b` 的順序，因為如果直接照輸入跑迴圈，反過來的情況就會出錯。

格式和邊界要寫對。下次遇到這種區間題，我會先確認輸入順序。
