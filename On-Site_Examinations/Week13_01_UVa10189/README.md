# UVa 10189 - Minesweeper

## 1. Problem Information

Platform: UVa
Problem ID: 10189
Problem Title: Minesweeper
Problem Link: https://onlinejudge.org/external/101/10189.pdf
Week: 13
Date: 2026/05/19
Theme: 2D Array
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10189.cpp`

## 2. Problem Statement in My Own Words

* 這題是經典的 minesweeper 題目。輸入一個地雷盤面，`*` 代表地雷，其他格子要輸出它周圍 8 格有幾個地雷。

### What is the input?

* 輸入有多組資料。
* 每組先輸入兩個整數 `n` 和 `m`。

  * `n` 是列數。
  * `m` 是行數。
* 接著輸入 `n` 行，每行有 `m` 個字元。
* 如果 `n = 0` 且 `m = 0`，代表輸入結束。

### What is the expected output?

* 每組資料要輸出：

```text 
Field #x:
```

* 接著輸出轉換後的 minesweeper 盤面。
* 不同 field 之間要空一行。

### What are the main rules or constraints?

* 如果原本格子是 `*`，輸出仍然是 `*`。
* 如果原本格子不是 `*`，要計算周圍 8 個方向有幾個地雷。
* 八個方向包含上、下、左、右和四個斜角。
* 檢查周圍格子時要注意邊界，不能超出陣列範圍。

### What is the core task you must solve?

* 對每個非地雷格子，檢查周圍 8 格並計算地雷數量。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到這題，可以直接用二維陣列或 `vector<string>` 存盤面。
* 對每個格子判斷是不是地雷。
* 如果不是地雷，就去掃它周圍 8 個方向。
* 這題主要小心輸出格式和邊界檢查。

### Final Strategy

* 每次讀入 `n` 和 `m`。
* 如果 `n == 0 && m == 0`，就結束。
* 用 `vector<string> board` 存整個盤面。
* 輸出 `Field #x:`。
* 對每個位置 `(i, j)`：

  * 如果 `board[i][j] == '*'`，直接輸出 `*`。
  * 否則設定 `count = 0`。
  * 用 `dx` 和 `dy` 從 `-1` 到 `1`，檢查周圍 8 格。
  * 跳過 `(dx, dy) = (0, 0)`，因為那是自己。
  * 如果新位置在合法範圍內，而且是 `*`，就讓 `count++`。
  * 最後輸出 `count`。
* 每個 field 之間輸出空行。

What edge cases did you consider?

* `n = 0` 且 `m = 0` 時要停止
* 地雷在邊界或角落
* 全部都是地雷
* 全部都不是地雷
* 不同 field 之間要空行
* 檢查 8 個方向時不能超出範圍

## 4. Pseudocode

```text 
START
1. Set field = 1.
2. While input has n and m:
3.     If n == 0 and m == 0:
4.         Stop the program.
5.     Read the board.
6.     If field > 1:
7.         Print a blank line.
8.     Print "Field #field:".
9.     For each cell (i, j):
10.        If board[i][j] is '*':
11.            Print '*'.
12.        Else:
13.            Set count = 0.
14.            For dx from -1 to 1:
15.                For dy from -1 to 1:
16.                    If dx == 0 and dy == 0:
17.                        Continue.
18.                    ni = i + dx.
19.                    nj = j + dy.
20.                    If ni and nj are inside the board:
21.                        If board[ni][nj] is '*':
22.                            count++.
23.            Print count.
24.     Increase field by 1.
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
#include <string>

using namespace std;

// A

int main()
{
    int n, m;
    int field = 1;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }

        vector<string> board(n);

        for (int i = 0; i < n; i++)
        {
            cin >> board[i];
        }

        if (field > 1)
        {
            cout << endl;
        }

        cout << "Field #" << field << ":" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '*')
                {
                    cout << '*';
                }
                else
                {
                    int count = 0;

                    for (int dx = -1; dx <= 1; dx++)
                    {
                        for (int dy = -1; dy <= 1; dy++)
                        {
                            if (dx == 0 && dy == 0)
                            {
                                continue;
                            }

                            int ni = i + dx;
                            int nj = j + dy;

                            if (ni >= 0 && ni < n && nj >= 0 && nj < m)
                            {
                                if (board[ni][nj] == '*')
                                {
                                    count++;
                                }
                            }
                        }
                    }

                    cout << count;
                }
            }

            cout << endl;
        }

        field++;
    }

    return 0;
}
```

Why it works:

* 程式用 `vector<string>` 保存原本的盤面。
* 對地雷格直接輸出 `*`，不會改變。
* 對非地雷格，使用雙層迴圈檢查周圍 8 個方向。
* 每次檢查前都有確認 `ni` 和 `nj` 是否在合法範圍內。
* 使用 `field` 控制 Field 編號，也用 `field > 1` 處理不同測資之間的空行。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code           |
| --------------- | ---------------- | ---------------------- |
| Logic           | 可能只檢查上下左右。       | 檢查完整 8 個方向。            |
| Edge Cases      | 可能邊界格子會超出陣列。     | 每次都先判斷 `ni`、`nj` 是否合法。 |
| Output Handling | 可能空行或 Field 格式錯。 | 用 `field` 控制格式和空行。     |
| Other           | 可能把 `*` 也算成數字。   | 遇到 `*` 直接輸出。           |

### Reflection

要小心八個方向和邊界判斷。用 `dx`、`dy` 來掃周圍格子很方便，不需要自己分開寫八種情況。

