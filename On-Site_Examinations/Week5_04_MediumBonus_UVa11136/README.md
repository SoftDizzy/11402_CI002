# UVa 11136 - Hoax or what

## 1. Problem Information

Platform: UVa
Problem ID: 11136
Problem Title: Hoax or what
Problem Link: https://onlinejudge.org/external/111/11136.pdf
Week: 5
Date: 2026/03/24
Theme: Sorting basics
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11136.cpp`

## 2. Problem Statement in My Own Words

* 這題每天會有一些新的帳單金額加入。每天都要從目前所有帳單裡面拿出最大金額和最小金額，計算它們的差，並把這兩張帳單移除。最後要輸出所有天數累積的差額總和。

### What is the input?

* 輸入有多組資料。
* 每組資料第一個數字是 `n`，代表有幾天。
* 如果 `n = 0`，代表輸入結束。
* 接下來每一天會先輸入一個整數 `k`，代表當天有幾張帳單。
* 後面接著輸入 `k` 個整數，代表帳單金額。

### What is the expected output?

* 對每一組資料，輸出累積的總差額。
* 每組答案輸出一行。

### What are the main rules or constraints?

* 每天都會把新的帳單加入目前的集合。
* 每天要找出目前所有帳單中的最大值和最小值。
* 把 `最大值 - 最小值` 加到總和。
* 用完後要把這兩張帳單移除。
* 金額可能重複，所以資料結構要能存重複值。
* 總和可能很大，所以使用 `long long` 比較安全。

### What is the core task you must solve?

* 快速找到目前帳單中的最大值和最小值，計算差額後移除它們，最後輸出累積差額。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以想到每天都排序一次，然後拿第一個和最後一個。
* 但是每天都有新資料加入，如果每次都重新排序會比較麻煩。
* 這題需要一直維持資料是排序好的狀態，而且帳單金額可能重複，所以我使用 `multiset`。

### Final Strategy

* 用 `multiset<int> bills` 存目前所有帳單金額。
* `multiset` 會自動排序，而且可以存重複值。
* 每天先讀入 `k` 張帳單，全部放進 `bills`。
* `bills.begin()` 是最小值。
* `prev(bills.end())` 是最大值。
* 把最大值減最小值加到 `total`。
* 接著把這兩筆資料從 `bills` 裡刪掉。
* 所有天數做完後輸出 `total`。

What edge cases did you consider?

* 帳單金額可能重複
* 每天加入的帳單數量不同
* 最大值和最小值要在加入當天帳單後再找
* 用完最大和最小後要移除
* 有多組資料，要讀到 `n = 0`
* 累積總和可能超過 int，所以用 `long long`

## 4. Pseudocode



```text
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Create an empty multiset bills.
5.     Set total = 0.
6.     Repeat for each day:
7.         Read k.
8.         Read k bill values and insert them into bills.
9.         Let low be the smallest value in bills.
10.        Let high be the largest value in bills.
11.        Add high - low to total.
12.        Remove low from bills.
13.        Remove high from bills.
14.    Print total.
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
#include <set>

using namespace std;

// B Bonus

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        multiset<int> bills;
        long long total = 0;

        for (int day = 0; day < n; day++)
        {
            int k;
            cin >> k;

            for (int i = 0; i < k; i++)
            {
                int value;
                cin >> value;
                bills.insert(value);
            }

            auto low = bills.begin();
            auto high = prev(bills.end());

            total += *high - *low;

            bills.erase(low);
            bills.erase(high);
        }

        cout << total << endl;
    }

    return 0;
}
```

Why it works:

* `multiset` 可以自動排序，也可以保存重複金額。
* 每天加入新帳單後，最小值就是 `begin()`，最大值就是 `prev(end())`。
* 程式把最大值和最小值的差加到 `total`。
* 加完後會刪除這兩張帳單，符合題目每天移除最大與最小帳單的規則。
* 使用 `long long total` 可以避免累積金額太大時出錯。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code           | Correct Code             |
| --------------- | ------------------- | ------------------------ |
| Logic           | 可能每天重新排序或沒有維持資料順序。  | 使用 `multiset` 自動維持排序。    |
| Edge Cases      | 可能用 `set`，導致重複金額消失。 | 使用 `multiset`，可以存重複帳單金額。 |
| Output Handling | 可能每一天輸出一次。          | 每組資料最後只輸出累積總和。           |
| Other           | 可能沒有刪除最大和最小帳單。      | 每天計算完差額後移除最大和最小。         |

### Reflection

如果用普通陣列，每天都要找最大和最小，會比較麻煩；用 `multiset` 就可以直接拿到排序後的最小和最大。

下次遇到這種需要一直加入資料、又要一直拿最大最小值的題目，我會先想到 `multiset` 或 priority queue。
