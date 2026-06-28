# UVa 10107 - What is the Median?

## 1. Problem Information

Platform: UVa
Problem ID: 10107
Problem Title: What is the Median?
Problem Link: https://onlinejudge.org/external/101/10107.pdf
Week: 6
Date: 2026/03/31
Theme: Median / order statistics
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10107.cpp`

## 2. Problem Statement in My Own Words

* 這題會一直輸入整數，每讀進一個新的數字，就要輸出目前所有已讀數字的中位數。

### What is the input?

* 輸入有很多個整數。
* 整數會一直輸入到 EOF。
* 每讀進一個整數，就要馬上處理一次。

### What is the expected output?

* 每讀進一個數字後，輸出目前所有數字的 median。
* 每次 median 輸出一行。
* 如果目前數字個數是奇數，中位數是排序後中間的數字。
* 如果目前數字個數是偶數，中位數是排序後中間兩個數字的平均。

### What are the main rules or constraints?

* 不是全部讀完才輸出，而是每讀一個數字就輸出一次。
* 每次都要根據目前已經讀進來的所有數字計算。
* 數字需要排序後才能找中位數。
* 偶數個數時，題目要輸出兩個中間值的整數平均。

### What is the core task you must solve?

* 維護目前已讀入的所有數字，並在每次加入新數字後找出目前的中位數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想法是把所有讀進來的數字存進 `vector`。
* 因為每加入一個新數字都要算 median，所以可以每次加入後重新排序。

### Final Strategy

* 建立一個 `vector<int> v` 存目前所有數字。
* 用 `while (cin >> x)` 一直讀到 EOF。
* 每讀一個數字，就把它放進 `v`。
* 對 `v` 排序。
* 如果 `v.size()` 是奇數：

  * 輸出 `v[n / 2]`。
* 如果 `v.size()` 是偶數：

  * 輸出 `(v[n / 2 - 1] + v[n / 2]) / 2`。

What edge cases did you consider?

* 只有一個數字時，中位數就是自己
* 數字個數是奇數
* 數字個數是偶數
* 輸入可能有很多筆，要讀到 EOF
* 每讀一筆就要輸出一次，不是最後才輸出

## 4. Pseudocode

```text
START
1. Create an empty vector v.
2. While input has integer x:
3.     Add x into v.
4.     Sort v.
5.     Let n = size of v.
6.     If n is odd:
7.         Print v[n / 2].
8.     Else:
9.         Print (v[n / 2 - 1] + v[n / 2]) / 2.
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

// A Bonus

int main()
{
    vector<int> v;
    int x;

    while (cin >> x)
    {
        v.push_back(x);
        sort(v.begin(), v.end());

        int n = v.size();

        if (n % 2 == 1)
        {
            cout << v[n / 2] << endl;
        }
        else
        {
            cout << (v[n / 2 - 1] + v[n / 2]) / 2 << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式用 `while (cin >> x)` 讀到 EOF。
* 每讀進一個新數字，就放進 `vector` 並重新排序。
* 排序後，如果數量是奇數，就直接取中間位置。
* 如果數量是偶數，就取中間兩個數字的平均。
* 因為每讀一筆資料就輸出一次，所以符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code         |
| --------------- | ------------------ | -------------------- |
| Logic           | 可能全部讀完才算一次 median。 | 每讀入一個數字就重新計算 median。 |
| Edge Cases      | 可能只處理奇數個資料。        | 同時處理奇數和偶數個資料。        |
| Output Handling | 可能輸出次數不夠。          | 每讀一個數字就輸出一行。         |
| Other           | 可能沒有排序就取中間值。       | 每次加入後都先排序。           |

### Reflection

不是等全部資料輸入完才算，而是每次有新數字加入後都要輸出目前的 median。

我學到中位數題目一定要先確認資料數量是奇數還是偶數。
如果是偶數，就要取中間兩個數字的平均。

