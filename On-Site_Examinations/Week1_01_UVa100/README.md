# UVa 100 - The 3n + 1 Problem

Use this template to review your coding performance for each problem. Write clearly and use your own words.

## 1. Problem Information

Platform: UVa  
Problem ID: 100  
Problem Title: The 3n + 1 Problem  
Problem Link: https://onlinejudge.org/external/1/100.pdf  
Week: 1  
Date: 2026/02/24  
Theme: I/O, EOF, absolute difference  
Category: On-site Easy  
Source Code (Fail): No failed version was saved  
Source Code (Correct/Accepted): `src/4_100.cpp`

## 2. Problem Statement in My Own Words

- 這題會給兩個整數 i 和 j，我要找出從 i 到 j 之間每一個數字的 3n + 1 cycle length，並輸出其中最大的 cycle length.

### What is the input?

- 輸入有很多行，每一行有兩個整數 i 和 j。
程式要一直讀到 EOF 為止.

### What is the expected output?

- i j maximum_cycle_length.
(i j 需照原本輸入的順序輸出)

### What are the main rules or constraints?

- 如果 n 是奇數，下一個數字是 3 * n + 1
如果 n 是偶數，下一個數字是 n / 2
一直重複直到 n 變成 1
從原本的 n 到最後的 1，總共經過的數字數量就是 cycle length

### What is the core task you must solve?

- 對輸入的兩個數字所形成的區間，逐一計算每個數字的 cycle length，然後找出最大值。

## 3. Thinking Logic and Solution Strategy


### Initial Thoughts

- 我一開始的想法是，直接把 i 到 j 中間的每個數字都跑一次 3n + 1 規 則，算出每個數字的 cycle length，再用一個變數記錄目前最大的 cycle  length。但是題目不一定是小到大，如果他是先給大再小，迴圈就會出錯。

### Final Strategy

- 先把原本輸入的 i 和 j 存起來，因為最後輸出要用原本順序。
接著用 min(i, j) 和 max(i, j) 找出真正要計算的範圍。
然後從範圍起點跑到終點，對每個數字計算 cycle length，並更新最大值。

What edge cases did you consider?

- i < j 的正常情況
- i > j 的反向輸入情況
- i == j，區間只有一個數字
- cycle length 要包含起始數字本身
- 輸出必須保留原本輸入順序
- 計算 3 * n + 1 時，數值可能變大，所以可以- 用 long long 來存運算中的 n

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. While input has two integers i and j: 2. Save original i and original j. 
3. Let start = smaller value of i and j. 4. Let end = larger value of i and j. 
5. Set maxCycle = 0. 
6. For each number n from start to end: 7. Calculate the cycle length of n. 
8. If this cycle length is greater than maxCycle: 
9. Update maxCycle. 
10. Print original i, original j, and maxCycle. 
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

// A

int main()
{
    int i,j;
    while ( cin >> i >> j )
    {

        int start = min( i , j );
        int end = max( i , j );

        int max_length = 0;
        for ( int i = start; i <= end; i++ )
        {
            int n = i;
            int length = 1;
            while ( n != 1 )
            {
                if ( n % 2 == 1 )
                {
                    n = 3 * n + 1;
                    length++;
                }
                else
                {
                    n = n / 2;
                    length++;
                }
            }
            if ( length > max_length )
            {
                max_length = length;
            }
        }
        cout << i << " " << j << " " << max_length << endl;
    }
}
```

Why it works:

正確版本可以用 EOF 持續讀取多組輸入。
程式會先保留原本的 i 和 j，確保輸出格式正確。
接著用較小值和較大值決定真正要計算的範圍。
對範圍內每個數字計算 cycle length，並記錄最大值。
最後輸出原本的兩個輸入數字和最大 cycle length。

## 6. Difference and Reflection

### Key Differences

直接使用 i j 去做，沒有處理邊界問題及正確計算範圍。

### Reflection

這題讓我學到，除了演算法本身，輸入輸出格式也非常重要。

輸入是否有多組資料並需要讀到 EOF。
輸入順序是否會影響輸出。
邊界情況像是反向區間或單一數字是否有處理到。
