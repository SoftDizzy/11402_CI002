# UVa 10908 - Large Square

## 1. Problem Information

Platform: UVa
Problem ID: 10908
Problem Title: Large Square
Problem Link: https://onlinejudge.org/external/109/10908.pdf
Week: 4
Date: 2026/03/17
Theme: Arrays + simulation
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/36_10908.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個字元矩陣，接著給幾個中心點座標。我要從每個中心點往外擴張，找出以這個點為中心、且裡面字元都一樣的最大正方形大小。

### What is the input?

* 第一行是測資數量。
* 每組測資會先輸入 `m`、`n`、`q`。

  * `m` 是 row 數量。
  * `n` 是 column 數量。
  * `q` 是查詢中心點的數量。
* 接著輸入 `m` 行字串，代表矩陣內容。
* 接著有 `q` 筆查詢，每筆有中心點座標 `r` 和 `c`。

### What is the expected output?

* 每組測資要先輸出原本的 `m n q`。
* 接著對每個查詢輸出最大正方形的邊長。
* 每筆答案輸出一行。

### What are the main rules or constraints?

* 正方形必須以查詢給的 `(r, c)` 為中心。
* 正方形邊長一定是奇數，例如 `1, 3, 5, 7...`
* 正方形裡面的所有字元都必須和中心點字元一樣。
* 擴張時不能超出矩陣邊界。
* 如果不能擴張，答案至少是 `1`。

### What is the core task you must solve?

* 核心任務是對每個中心點，嘗試往外擴張正方形，並檢查擴張後的範圍是否全部都是同一個字元。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始我想法是直接從中心點開始，一層一層往外擴張。
* 每次擴張後，檢查目前方形範圍內的字元是不是都跟中心點一樣。
* 這題比較要注意的是邊界，因為中心點如果靠近矩陣邊緣，很快就不能再擴張。

### Final Strategy

* 先用 `vector<string>` 存整個矩陣。
* 對每個查詢 `(r, c)`，先記錄中心點字元 `target = v[r][c]`。
* 設定初始答案 `length = 1`。
* 用 `k` 表示目前往外擴張幾格。
* 每次根據 `k` 算出正方形的四個邊界：

  * `top = r - k`
  * `bottom = r + k`
  * `left = c - k`
  * `right = c + k`
* 如果邊界超出矩陣，就停止擴張。
* 否則檢查這個方形裡面的每個字元。
* 如果全部都等於 `target`，就更新 `length = 2 * k + 1`。
* 如果有不同的字元，就停止，輸出目前最大長度。

What edge cases did you consider?

* 中心點在邊界附近
* 答案只有 `1`
* 正方形擴張後超出矩陣
* 方形裡面只要有一個字元不同就要停止
* 有多組測資
* 每組測資要先輸出 `m n q`

## 4. Pseudocode



```
START
1. Read testbase.
2. For each test case:
3.     Read m, n, q.
4.     Read the matrix into vector v.
5.     Print m, n, q.
6.     For each query:
7.         Read r and c.
8.         Set target = v[r][c].
9.         Set length = 1.
10.        For k = 1 and keep increasing:
11.            Calculate top, bottom, left, and right.
12.            If the square is outside the matrix:
13.                Stop expanding.
14.            Check every cell inside the square.
15.            If all cells are the same as target:
16.                length = 2 * k + 1.
17.            Else:
18.                Stop expanding.
19.        Print length.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```
No failed version was saved.
```

Why it failed:

* No failed version was saved.

### Correct Code

```cpp
#include <iostream>
#include <vector>
#include <string>

/*
    給你矩陣大小與字母，以及 q 個 測試中心點以及座標，要你算出中心點往外擴張後，若範圍內的字母都與中心點一的話就是符合題目要求，並要你算出最大擴張後的方形大小
*/
using namespace std;

//      B

int main()
{
    int testbase;
    cin >> testbase;    //幾組側資

    while (testbase--)
    {
        int m, n, q;                // m 個 row ， n 個 column ， q 個中心點
        cin >> m >> n >> q;

        vector<string> v(m);        // 設個陣列 大小為 m ( row )

        for (int i = 0; i < m; i++) // 依序往下讀取 row    v[0] = "aaaabbbbcc"
        {
            cin >> v[i];            // cin column         v[1] = "aacccbbbbb"
        }

        cout << m << " " << n << " " << q << endl;

        while (q--)                // 幾個中心點
        {
            int r, c;              // 中心座標
            cin >> r >> c;

            char target = v[r][c];

            int length = 1;         // 最小就是 1 

            for (int k = 1; ; k++)  // 設置擴張的大小 從 1　開始
            {
                int top = r - k;    // 設置擴張方形的邊界  要記住 這題的起始點是左上， ( m , n )是在右下角
                int bottom = r + k;
                int left = c - k;
                int right = c + k;

                if (top < 0 || bottom >= m || left < 0 || right >= n)       // 測試是否有邊界問題
                {
                    break;
                }

                bool ok = true;

                for (int i = top; i <= bottom; i++)
                {
                    for (int j = left; j <= right; j++)
                    {
                        if (v[i][j] != target)                 // 測試方形裡面是不是都與中心一樣
                        {
                            ok = false;
                            break;
                        }
                    }

                    if (ok == false)
                    {
                        break;
                    }
                }

                if (ok == true)
                {
                    length = 2 * k + 1;
                }
                else
                {
                    break;
                }
            }

            cout << length << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式先把矩陣存進 `vector<string>`，查詢時可以直接用座標取字元。
* 每個查詢都先找出中心點字元 `target`。
* 用 `k` 控制擴張範圍，並用 `top`、`bottom`、`left`、`right` 算出目前正方形邊界。
* 擴張前先檢查是否超出矩陣邊界。
* 如果沒有超出，就檢查正方形內所有字元是否都等於中心字元。
* 只要全部相同，就更新最大邊長；如果不同就停止。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code                            |
| --------------- | ---------------- | --------------------------------------- |
| Logic           | 可能只看中心點或只檢查一部分。  | 從中心點一層一層擴張，並檢查整個方形。                     |
| Edge Cases      | 可能沒有處理矩陣邊界。      | 每次擴張前都檢查 `top`、`bottom`、`left`、`right`。 |
| Output Handling | 可能忘記先輸出 `m n q`。 | 每組測資先輸出 `m n q`，再輸出各查詢答案。               |
| Other           | 可能邊長計算錯。         | 使用 `2 * k + 1` 計算目前正方形邊長。               |

### Reflection

這題我覺得最重要的是邊界判斷。
只要中心點靠近邊界，擴張時就很容易超出矩陣，所以要先檢查範圍再去跑迴圈。

下次遇到這種從中心往外擴張的題目，要先把上下左右邊界變數寫清楚，這樣比較不容易搞錯。
