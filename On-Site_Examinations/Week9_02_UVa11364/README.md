# UVa 11364 - Optimal Parking

## 1. Problem Information

Platform: UVa
Problem ID: 11364
Problem Title: Optimal Parking
Problem Link: https://onlinejudge.org/external/113/11364.pdf
Week: 9
Date: 2026/04/21
Theme: Prefix sums / difference arrays
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11364.cpp`

## 2. Problem Statement in My Own Words

* 這題會給幾間商店的位置，要找出最短的走路距離。車可以停在某個位置，然後要走到所有商店再回來。

### What is the input?

* 第一行是測資數量。
* 每組測資先輸入一個整數 `n`，代表商店數量。
* 接著輸入 `n` 個整數，代表每間商店的位置。

### What is the expected output?

* 每組測資輸出最短需要走的距離。
* 每筆答案輸出一行。

### What are the main rules or constraints?

* 只需要考慮最左邊和最右邊的商店。
* 不管車停在哪裡，最短距離都會等於最右邊商店和最左邊商店距離的兩倍。
* 因為要走到所有商店並回來，所以要乘以 2。

### What is the core task you must solve?

* 找出商店位置的最大值和最小值，然後計算：

```text
(max_position - min_position) * 2
```

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可能會想要找車停在哪裡比較好。
* 但其實只要走過所有商店，最遠一定會涵蓋最左邊到最右邊這段距離。
* 來回一次，所以答案就是這段距離乘以 2。

### Final Strategy

* 讀入測資數量。
* 每組讀入所有商店位置。
* 把商店位置排序。
* 排序後第一個是最左邊商店，最後一個是最右邊商店。
* 用 `(shops[n - 1] - shops[0]) * 2` 算出答案。
* 輸出答案。

What edge cases did you consider?

* 商店位置沒有照順序輸入
* 只有少量商店
* 最左和最右商店距離決定答案
* 有多組測資
* 每組答案都要換行

## 4. Pseudocode

```text
START
1. Read testCase.
2. Repeat for each test case:
3.     Read n.
4.     Read n shop positions into vector.
5.     Sort the shop positions.
6.     distance = (last position - first position) * 2.
7.     Print distance.
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

// B

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int n;
        cin >> n;

        vector<int> shops(n);

        for (int i = 0; i < n; i++)
        {
            cin >> shops[i];
        }

        sort(shops.begin(), shops.end());

        int distance = (shops[n - 1] - shops[0]) * 2;

        cout << distance << endl;
    }

    return 0;
}
```

Why it works:

* 程式先把所有商店位置讀進 vector。
* 排序後可以直接得到最左邊和最右邊的商店位置。
* 最短需要走的距離就是這兩點距離的來回，所以乘以 2。
* 每組測資都獨立處理並輸出一行。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code     | Correct Code          |
| --------------- | ------------- | --------------------- |
| Logic           | 可能想找最佳停車點。    | 只需要找最左和最右商店。          |
| Edge Cases      | 可能商店位置未排序時算錯。 | 先排序再取第一個和最後一個。        |
| Output Handling | 可能忘記每組測資輸出一行。 | 每組輸出一次距離。             |
| Other           | 可能忘記來回要乘以 2。  | 使用 `(max - min) * 2`。 |

### Reflection

重點是看出只要考慮最左和最右的商店。
不用真的去枚舉停車位置，因為不管停在哪裡，最短路徑都會涵蓋整個商店範圍。其實只要找出最大值和最小值就可以。

