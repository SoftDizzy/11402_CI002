# UVa 410 - Station Balance

## 1. Problem Information

Platform: UVa
Problem ID: 410
Problem Title: Station Balance
Problem Link: https://onlinejudge.org/external/4/410.pdf
Week: 17
Date: Not specified
Theme: Greedy / Sorting
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/410.cpp`

## 2. Problem Statement in My Own Words

* 這題有 `C` 個 chambers 和 `S` 個 specimens。
* 每個 chamber 最多可以放 2 個 specimen。
* 我要把 specimens 分配到 chambers 裡，讓每個 chamber 的總重量盡量接近平均重量。
* 最後要輸出每個 chamber 放了哪些 specimens，還有整體 imbalance。

### What is the input?

* 輸入有多組資料，要一直讀到 EOF。
* 每組資料先輸入兩個整數：

  * `C`：chamber 數量
  * `S`：specimen 數量
* 接著輸入 `S` 個 specimen 的重量。

### What is the expected output?

* 每組資料要輸出：

```text
Set #x
```

* 接著輸出每個 chamber 裡面的 specimen。
* 最後輸出：

```text 
IMBALANCE = value
```

* `IMBALANCE` 要輸出到小數點後 5 位。
* 每組資料後面要空一行。

### What are the main rules or constraints?

* 每個 chamber 最多放 2 個 specimen。
* 總共有 `2 * C` 個可放位置。
* 如果 specimen 不足 `2 * C` 個，可以補重量 `0`。
* 為了讓每個 chamber 重量接近平均，通常把最輕的和最重的配在一起。
* imbalance 是每個 chamber 重量和平均重量差距的總和。

### What is the core task you must solve?

* 排序 specimens，將最輕和最重配對，並計算每個 chamber 的 imbalance。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果隨便分配，可能會讓某些 chamber 特別重，某些 chamber 很輕。
* 因為每個 chamber 最多放兩個 specimen，所以可以把重量大的和重量小的配在一起。
* 這樣每組的總重量會比較平均。

### Final Strategy

* 每組讀入 `C` 和 `S`。
* 建立大小為 `2 * C` 的 `mass`，先全部補 0。
* 讀入 `S` 個 specimen 重量，順便累加 `totalMass`。
* 將 `mass` 排序。
* 平均重量為：

```text
average = totalMass / C
```

* 對每個 chamber `i`：

  * 配對 `mass[i]` 和 `mass[2 * C - 1 - i]`
  * 也就是最輕配最重。
* chamber 重量為兩者相加。
* imbalance 加上：

```text 
abs(chamberMass - average)
```

* 最後輸出每個 chamber 的內容和總 imbalance。

What edge cases did you consider?

* `S` 小於 `2 * C`，需要補 0
* 某個 chamber 可能只有一個 specimen
* 某個 chamber 可能沒有 specimen
* specimen 重量輸出時不要印 0
* imbalance 要輸出小數點後 5 位
* 輸入有多組，要讀到 EOF

## 4. Pseudocode

```text 
START
1. Set cases = 1.
2. While input has C and S:
3.     Create mass array with size 2 * C, initialized with 0.
4.     Set totalMass = 0.
5.     Read S specimen weights.
6.     Store them into mass and add to totalMass.
7.     Sort mass.
8.     average = totalMass / C.
9.     Set imbalance = 0.
10.    Print "Set #cases".
11.    For i from 0 to C - 1:
12.        left = mass[i].
13.        right = mass[2 * C - 1 - i].
14.        Print chamber index and non-zero specimens.
15.        chamberMass = left + right.
16.        imbalance += abs(chamberMass - average).
17.    Print "IMBALANCE = imbalance" with 5 decimal places.
18.    Print blank line.
19.    cases++.
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
#include <iomanip>
#include <cmath>

using namespace std;

// B

int main()
{
    int C, S;
    int cases = 1;

    while (cin >> C >> S)
    {
        vector<int> mass(2 * C, 0);

        int totalMass = 0;

        for (int i = 0; i < S; i++)
        {
            cin >> mass[i];
            totalMass += mass[i];
        }

        sort(mass.begin(), mass.end());

        double average = (double)totalMass / C;
        double imbalance = 0.0;

        cout << "Set #" << cases << endl;

        for (int i = 0; i < C; i++)
        {
            int left = mass[i];
            int right = mass[2 * C - 1 - i];

            cout << " " << i << ":";

            if (left != 0)
            {
                cout << " " << left;
            }

            if (right != 0)
            {
                cout << " " << right;
            }

            cout << endl;

            int chamberMass = left + right;
            imbalance += abs(chamberMass - average);
        }

        cout << fixed << setprecision(5);
        cout << "IMBALANCE = " << imbalance << endl << endl;

        cases++;
    }

    return 0;
}
```

Why it works:

* `mass` 一開始開成 `2 * C` 個位置，沒有 specimen 的位置會自動補 0。
* 排序後，`mass[i]` 是偏輕的一端，`mass[2 * C - 1 - i]` 是偏重的一端。
* 把輕的和重的配在一起，可以讓每個 chamber 的重量比較平均。
* 輸出時只印非 0 的 specimen，補位的 0 不會出現在答案中。
* `average` 使用 double 計算，imbalance 也用 double 累加。
* `fixed << setprecision(5)` 可以讓 imbalance 符合題目格式。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                       | Correct Code                      |
| --------------- | ------------------------------- | --------------------------------- |
| Logic           | 可能直接照輸入順序分配。                    | 排序後最輕配最重。                         |
| Edge Cases      | 可能沒補 0，導致 chamber 數量不完整。        | 使用大小 `2 * C` 的陣列，缺的位置補 0。         |
| Output Handling | 可能印出補位的 0 或小數格式錯。               | 只印非 0 specimen，imbalance 印 5 位小數。 |
| Other           | 可能讓重量大的 specimen 集中在同一 chamber。 | 用 greedy 配對讓重量較平均。                |

### Reflection


我覺得重點是先把 chamber 想成 `2 * C` 個位置，缺少的 specimen 用 0 補齊。

排序後最輕配最重，可以避免重量大的 specimen 集中在同一個 chamber。
這樣每個 chamber 的總重量比較接近平均值，imbalance 也會比較小。
