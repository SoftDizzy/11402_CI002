# UVa 10341 - Solve It

## 1. Problem Information

Platform: UVa
Problem ID: 10341
Problem Title: Solve It
Problem Link: https://onlinejudge.org/external/103/10341.pdf
Week: 7
Date: 2026/04/07
Theme: Binary search
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10341.cpp`

## 2. Problem Statement in My Own Words

* 這題會給六個係數 `p q r s t u`，我要在 `0 <= x <= 1` 的範圍內找出方程式的解。如果找不到解，就輸出 `No solution`。

### What is the input?

* 輸入有多組資料。
* 每組資料有六個整數：

```text
p q r s t u
```

* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 如果在 `0` 到 `1` 之間有解，就輸出 `x`，並四捨五入到小數點後 4 位。
* 如果沒有解，就輸出：

```text
No solution
```

### What are the main rules or constraints?

* 要解的函數是：

```text
p * e^(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x^2 + u = 0
```

* 解只需要找 `0 <= x <= 1` 之間的值。
* 輸出答案要固定小數點後 4 位。
* 如果 `f(0)` 和 `f(1)` 同號，代表區間內可能沒有解，可以輸出 `No solution`。
* 可以用二分法一直縮小區間。

### What is the core task you must solve?

* 判斷方程式在 `[0, 1]` 之間是否有解，若有解就用 binary search 找到足夠精準的 `x`。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到這題的函數很複雜，不太可能手動解出公式。
* 但題目只要求在 `0` 到 `1` 之間找解，而且只要輸出到小數點後 4 位。
* 所以可以用二分法慢慢逼近答案。

### Final Strategy

* 先寫一個 `f(x)` 函式，根據輸入的 `p q r s t u` 計算函數值。
* 每組資料先算 `f(0)` 和 `f(1)`。
* 如果兩端點有一個剛好是 0，就直接輸出該端點。
* 如果 `f(0)` 和 `f(1)` 同號，就輸出 `No solution`。
* 否則就用二分法：

  * 取 `mid = (left + right) / 2`
  * 算 `f(mid)`
  * 如果 `f(left)` 和 `f(mid)` 同號，代表解在右半邊
  * 否則解在左半邊
* 重複多次後，答案就會很接近真正的解。

What edge cases did you consider?

* `x = 0` 剛好是解
* `x = 1` 剛好是解
* `[0, 1]` 之間沒有解
* 浮點數不能只靠一次計算，要多跑幾輪二分法
* 輸出要固定小數點後 4 位
* 有多組輸入，要讀到 EOF

## 4. Pseudocode

```text
START
1. While input has p, q, r, s, t, u:
2.     Set left = 0 and right = 1.
3.     Calculate f(left) and f(right).
4.     If f(left) is 0:
5.         Print left with 4 decimal places.
6.     Else if f(right) is 0:
7.         Print right with 4 decimal places.
8.     Else if f(left) and f(right) have the same sign:
9.         Print "No solution".
10.    Else:
11.        Repeat binary search many times:
12.            mid = (left + right) / 2.
13.            If f(left) and f(mid) have the same sign:
14.                left = mid.
15.            Else:
16.                right = mid.
17.        Print (left + right) / 2 with 4 decimal places.
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
#include <iomanip>
#include <cmath>

using namespace std;

// B Bonus

int p, q, r, s, t, u;

double f(double x)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main()
{
    while (cin >> p >> q >> r >> s >> t >> u)
    {
        double left = 0.0;
        double right = 1.0;

        double fLeft = f(left);
        double fRight = f(right);

        if (fLeft == 0)
        {
            cout << fixed << setprecision(4) << left << endl;
        }
        else if (fRight == 0)
        {
            cout << fixed << setprecision(4) << right << endl;
        }
        else if (fLeft * fRight > 0)
        {
            cout << "No solution" << endl;
        }
        else
        {
            for (int i = 0; i < 100; i++)
            {
                double mid = (left + right) / 2.0;
                double fMid = f(mid);

                if (fLeft * fMid > 0)
                {
                    left = mid;
                    fLeft = fMid;
                }
                else
                {
                    right = mid;
                    fRight = fMid;
                }
            }

            double ans = (left + right) / 2.0;
            cout << fixed << setprecision(4) << ans << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式把題目的公式寫成 `f(x)`，每次只要傳入 `x` 就能算出函數值。
* 先用 `f(0)` 和 `f(1)` 判斷是否可能有解。
* 如果兩端點同號，代表在這個範圍內沒有跨過 0，所以輸出 `No solution`。
* 如果有解，就用二分法不斷縮小範圍。
* 迴圈跑 100 次後精度已經足夠，最後輸出小數點後 4 位。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code     | Correct Code                           |
| --------------- | ------------- | -------------------------------------- |
| Logic           | 可能想直接用公式解。    | 使用二分法逼近答案。                             |
| Edge Cases      | 可能沒處理無解情況。    | 用 `f(0)` 和 `f(1)` 的正負判斷 `No solution`。 |
| Output Handling | 可能沒有固定 4 位小數。 | 使用 `fixed` 和 `setprecision(4)`。        |
| Other           | 可能二分次數太少。     | 固定跑 100 次，精度足夠。                        |

### Reflection

這題讓我知道 binary search 也可以用在找方程式的近似解。
只要函數在某個範圍內有單調性，或可以用正負號判斷解在哪一邊，就能用二分法逼近。

