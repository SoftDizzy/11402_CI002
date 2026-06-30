# UVa 102 - Ecological Bin Packing

## 1. Problem Information

Platform: UVa
Problem ID: 102
Problem Title: Ecological Bin Packing
Problem Link: https://onlinejudge.org/external/1/102.pdf
Week: 17
Date: Not specified
Theme: Brute Force / Greedy Checking
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/102.cpp`

## 2. Problem Statement in My Own Words

* 這題有 3 個 bin，每個 bin 裡面都有 Brown、Green、Clear 三種瓶子。
* 最後每個 bin 只能放一種顏色的瓶子。
* 我要決定三個 bin 分別放哪一種顏色，讓需要移動的瓶子數量最少。
* 如果有多種答案移動數一樣，要輸出字典序最小的排列。

### What is the input?

* 輸入有多組資料，要一直讀到 EOF。
* 每組資料有 9 個整數。
* 代表 3 個 bin 裡面各自有 B、G、C 三種瓶子的數量。

### What is the expected output?

* 每組資料輸出一行。
* 輸出最佳排列和最少移動數，例如：

```text 
BCG 30
```

### What are the main rules or constraints?

* 每個 bin 最後只能保留一種顏色的瓶子。
* 不屬於該 bin 指定顏色的瓶子都要移走。
* 總共有 3 種顏色，所以排列只有 6 種。
* 如果移動數相同，要選字典序最小的排列。

### What is the core task you must solve?

* 檢查 6 種顏色排列，計算每種排列需要移動的瓶子數，找出最小答案。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以想到直接嘗試所有可能的顏色分配。
* 因為只有 3 個 bin 和 3 種顏色，所以全部排列只有 6 種，不需要複雜演算法。
* 對每個排列來說，如果某個 bin 指定放某種顏色，那這個 bin 裡同顏色的瓶子可以留下，其餘都要移走。

### Final Strategy

* 先讀入 3x3 的瓶子數量。
* 建立 6 種可能排列：

```text 
BCG
BGC
CBG
CGB
GBC
GCB
```

* 先計算全部瓶子總數 `total`。
* 對每一種排列：

  * 計算每個 bin 可以留下多少瓶子。
  * `keep` 代表不用移動的瓶子數。
  * 需要移動的瓶子數就是：

```text 
move = total - keep
```

* 如果 `move` 比目前最佳答案小，就更新答案。
* 因為排列順序已經是字典序，所以相同移動數時不更新，就會保留字典序較小的答案。

What edge cases did you consider?

* 多種排列移動數相同
* 某個 bin 裡某顏色瓶子數量是 0
* 所有瓶子都已經在正確 bin 中
* 每組輸入都要重新計算 total 和 bestMove
* 要一直讀到 EOF
* 顏色字元要正確轉成 index

## 4. Pseudocode

```text 
START
1. While input has 9 bottle numbers:
2.     Store them in bottle[3][3].
3.     Create the 6 possible orders in lexicographic order.
4.     Calculate total number of bottles.
5.     Set bestMove = infinity.
6.     For each order:
7.         Set keep = 0.
8.         For each bin from 0 to 2:
9.             Convert order[bin] to color index.
10.            keep += bottle[bin][color].
11.        move = total - keep.
12.        If move < bestMove:
13.            bestMove = move.
14.            bestOrder = order.
15.    Print bestOrder and bestMove.
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
#include <string>
#include <vector>
#include <climits>

using namespace std;

// A Bonus

int colorIndex(char c)
{
    if (c == 'B')
    {
        return 0;
    }
    else if (c == 'G')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int main()
{
    int bottle[3][3];

    while (cin >> bottle[0][0] >> bottle[0][1] >> bottle[0][2]
               >> bottle[1][0] >> bottle[1][1] >> bottle[1][2]
               >> bottle[2][0] >> bottle[2][1] >> bottle[2][2])
    {
        vector<string> orders;
        orders.push_back("BCG");
        orders.push_back("BGC");
        orders.push_back("CBG");
        orders.push_back("CGB");
        orders.push_back("GBC");
        orders.push_back("GCB");

        int total = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                total += bottle[i][j];
            }
        }

        string bestOrder;
        int bestMove = INT_MAX;

        for (int i = 0; i < orders.size(); i++)
        {
            string order = orders[i];

            int keep = 0;

            for (int bin = 0; bin < 3; bin++)
            {
                int color = colorIndex(order[bin]);
                keep += bottle[bin][color];
            }

            int move = total - keep;

            if (move < bestMove)
            {
                bestMove = move;
                bestOrder = order;
            }
        }

        cout << bestOrder << " " << bestMove << endl;
    }

    return 0;
}
```

Why it works:

* 程式把 3 個 bin 和 3 種顏色的瓶子數量存在 `bottle[3][3]`。
* `colorIndex()` 可以把 `B`、`G`、`C` 轉成陣列 index。
* 6 種排列全部檢查，所以不會漏掉可能答案。
* 對每個排列，先算可以留在原 bin 的瓶子數 `keep`。
* 需要移動的數量是 `total - keep`。
* 因為排列是照字典序放入 vector，所以遇到相同移動數時不更新，就會保留字典序較小的答案。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code            |
| --------------- | --------------- | ----------------------- |
| Logic           | 可能只嘗試部分排列。      | 檢查全部 6 種排列。             |
| Edge Cases      | 可能移動數相同時選錯。     | 排列照字典序檢查，相同時保留先出現者。     |
| Output Handling | 可能只輸出移動數。       | 輸出最佳排列和最少移動數。           |
| Other           | 可能顏色 index 對應錯。 | 使用 `colorIndex()` 統一轉換。 |

### Reflection

我覺得重點是移動數的計算方式：與其直接算要移走多少，不如先算可以留下多少，再用總數扣掉。

這題也提醒我，題目如果要求字典序最小，檢查順序就很重要。
只要先把排列照字典序排好，遇到相同答案時不要更新，就可以自然保留正確答案。
