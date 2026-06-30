# UVa 10954 - Add All

## 1. Problem Information

Platform: UVa
Problem ID: 10954
Problem Title: Add All
Problem Link: https://onlinejudge.org/external/109/10954.pdf
Week: 14
Date: 2026/05/26
Theme: Heap / Priority Queue
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10954.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一堆數字，每次可以選兩個數字相加。
* 每次相加的結果會產生成本，並且相加後的新數字還要放回去繼續合併。
* 目標是讓全部數字合併成一個數字時，總成本最小。

### What is the input?

* 輸入有多組資料。
* 每組先輸入一個整數 `n`，代表有幾個數字。
* 接著輸入 `n` 個整數。
* 如果 `n = 0`，代表輸入結束。

### What is the expected output?

* 對每組資料輸出一個整數。
* 這個整數代表最小總合併成本。

### What are the main rules or constraints?

* 每次只能選兩個數字相加。
* 相加的結果會放回資料中，繼續參與下一次合併。
* 每次相加的值都要加到總成本。
* 為了讓總成本最小，每次都應該選目前最小的兩個數字合併。

### What is the core task you must solve?

* 使用 min heap，每次快速取出最小的兩個數字，計算最小合併成本。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果每次都用排序找最小兩個數字，雖然可以做，但每次重新排序會比較麻煩。
* 這題每次都需要取出目前最小值，所以很適合用 priority queue。
* C++ 的 `priority_queue` 預設是 max heap，所以要改成 min heap。

### Final Strategy

* 每次讀入 `n`。
* 如果 `n == 0`，就結束。
* 建立 min heap：

```text 
priority_queue<int, vector<int>, greater<int>>
```

* 把所有數字放進 min heap。
* 當 heap 裡面還有超過一個數字時：

  * 取出最小的數字 `a`。
  * 再取出第二小的數字 `b`。
  * 計算 `sum = a + b`。
  * 把 `sum` 加到總成本 `cost`。
  * 再把 `sum` 放回 heap。
* 最後輸出 `cost`。

What edge cases did you consider?

* `n = 0` 時要停止
* 只有一個數字時，不需要合併，成本是 0
* 數字合併很多次後，總成本可能比較大，所以用 `long long`
* 每次都要取目前最小的兩個數字
* 合併後的新數字也要放回 heap

## 4. Pseudocode

```text 
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Create a min heap pq.
5.     Repeat n times:
6.         Read x.
7.         Push x into pq.
8.     Set cost = 0.
9.     While pq has more than one number:
10.        a = smallest number in pq.
11.        Pop a.
12.        b = smallest number in pq.
13.        Pop b.
14.        sum = a + b.
15.        cost += sum.
16.        Push sum back into pq.
17.    Print cost.
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
#include <queue>
#include <vector>
#include <functional>

using namespace std;

// A Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            pq.push(x);
        }

        long long cost = 0;

        while (pq.size() > 1)
        {
            int a = pq.top();
            pq.pop();

            int b = pq.top();
            pq.pop();

            int sum = a + b;
            cost += sum;

            pq.push(sum);
        }

        cout << cost << endl;
    }

    return 0;
}
```

Why it works:

* min heap 可以讓程式每次快速拿到目前最小的數字。
* 每次合併最小的兩個數字，可以讓後面累積的成本最小。
* 合併後的 `sum` 會重新放回 heap，繼續參與下一輪合併。
* 當 heap 只剩一個數字時，代表全部都已經合併完成。
* `cost` 使用 `long long`，可以避免總成本太大時溢位。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code                   |
| --------------- | ---------------- | ------------------------------ |
| Logic           | 可能任意選兩個數字合併。     | 每次選目前最小的兩個數字。                  |
| Edge Cases      | 可能忘記 `n = 0` 結束。 | 遇到 `n == 0` 就停止。               |
| Output Handling | 可能只輸出最後合併結果。     | 輸出所有合併成本的總和。                   |
| Other           | 可能用 max heap。    | 使用 `greater<int>` 建立 min heap。 |

### Reflection

我一開始會以為只要一直相加就好，但其實順序會影響總成本。

每次選最小的兩個數字合併，後面的累積成本才會最小。
這個想法跟 Huffman coding 很像，都是用 greedy 加 min heap 處理。

