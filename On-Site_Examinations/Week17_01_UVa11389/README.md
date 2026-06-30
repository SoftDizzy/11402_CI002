# UVa 11389 - The Bus Driver Problem

## 1. Problem Information

Platform: UVa
Problem ID: 11389
Problem Title: The Bus Driver Problem
Problem Link: https://onlinejudge.org/external/113/11389.pdf
Week: 17
Date: Not specified
Theme: Greedy / Sorting
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11389.cpp`

## 2. Problem Statement in My Own Words

* 這題有 `n` 個 bus drivers，每個 driver 要負責一條 morning route 和一條 evening route。
* 如果一個 driver 當天兩條 route 的總長度超過 `d`，超過的部分就要付 overtime。
* 每超過 1 單位要付 `r` 元。
* 我要安排 morning routes 和 evening routes 的配對方式，讓總 overtime cost 最小。

### What is the input?

* 輸入有多組資料。
* 每組資料先輸入三個整數：

  * `n`：driver 數量
  * `d`：每天不需加班的最大路線長度
  * `r`：每單位 overtime 的費用
* 接著輸入 `n` 個 morning route 長度。
* 再輸入 `n` 個 evening route 長度。
* 如果輸入是 `0 0 0`，代表結束。

### What is the expected output?

* 每組資料輸出一個整數。
* 這個整數代表最小 overtime cost。

### What are the main rules or constraints?

* 每個 driver 一定要配一條 morning route 和一條 evening route。
* 每條 route 只能被使用一次。
* 如果 `morning + evening > d`，超過的部分要付 overtime。
* 目標是讓全部 drivers 的 overtime cost 最小。
* 可以透過排序讓配對更平均。

### What is the core task you must solve?

* 用 greedy 配對 morning routes 和 evening routes，讓超過 `d` 的總長度最小。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果隨便配對，可能會讓長的 morning route 又配到長的 evening route，這樣 overtime 會變很多。
* 所以應該把短的 route 和長的 route 配在一起，讓每天總長度比較平均。
* 這題適合用 greedy 加 sorting。

### Final Strategy

* 每次讀入 `n`、`d`、`r`。
* 如果三個都是 0，就結束。
* 讀入 morning routes 和 evening routes。
* 將 morning routes 由小到大排序。
* 將 evening routes 由大到小排序。
* 讓最短 morning 配最長 evening，第二短 morning 配第二長 evening。
* 對每一組配對計算：

```text 
total = morning[i] + evening[i]
```

* 如果 `total > d`，就把超過的部分加到 `overtime`。
* 最後輸出：

```text 
overtime * r
```

What edge cases did you consider?

* `n = 0, d = 0, r = 0` 時要停止
* 所有配對都沒有 overtime
* 所有配對都有 overtime
* morning 和 evening 原本輸入沒有排序
* overtime 要先加總超過的長度，最後再乘上 `r`
* 每組資料都要重新計算一次

## 4. Pseudocode

```text 
START
1. While input has n, d, r:
2.     If n == 0 and d == 0 and r == 0:
3.         Stop the program.
4.     Read morning routes.
5.     Read evening routes.
6.     Sort morning routes in increasing order.
7.     Sort evening routes in decreasing order.
8.     Set overtime = 0.
9.     For i from 0 to n - 1:
10.        total = morning[i] + evening[i].
11.        If total > d:
12.            overtime += total - d.
13.    Print overtime * r.
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

// A

int main()
{
    int n, d, r;

    while (cin >> n >> d >> r)
    {
        if (n == 0 && d == 0 && r == 0)
        {
            break;
        }

        vector<int> morning(n);
        vector<int> evening(n);

        for (int i = 0; i < n; i++)
        {
            cin >> morning[i];
        }

        for (int i = 0; i < n; i++)
        {
            cin >> evening[i];
        }

        sort(morning.begin(), morning.end());
        sort(evening.begin(), evening.end(), greater<int>());

        int overtime = 0;

        for (int i = 0; i < n; i++)
        {
            int total = morning[i] + evening[i];

            if (total > d)
            {
                overtime += total - d;
            }
        }

        cout << overtime * r << endl;
    }

    return 0;
}
```

Why it works:

* morning routes 由小到大排序，evening routes 由大到小排序。
* 這樣可以讓短路線配長路線，避免長路線互相配在一起造成更多 overtime。
* 每組配對只要超過 `d`，就把超過的長度加進 `overtime`。
* 最後再乘上 `r`，得到真正要付的 overtime cost。
* 遇到 `0 0 0` 時會正確停止。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                        |
| --------------- | ------------------ | ----------------------------------- |
| Logic           | 可能直接照輸入順序配對。       | 使用排序後的 greedy 配對。                   |
| Edge Cases      | 可能沒有處理 `0 0 0`。    | 遇到 `0 0 0` 就停止。                     |
| Output Handling | 可能只輸出 overtime 長度。 | 輸出 `overtime * r`。                  |
| Other           | 可能讓長路線配長路線。        | 讓短 morning 配長 evening，降低總 overtime。 |

### Reflection

我覺得關鍵是不要讓長的 morning route 再配到長的 evening route，不然 overtime 會變多。

把 morning 排小到大，evening 排大到小後，每個 driver 的總長度會比較平均。
這樣可以讓超過 `d` 的總量變小。
