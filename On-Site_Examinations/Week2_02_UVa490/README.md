# UVa 490 - Rotating Sentences

## 1. Problem Information

Platform: UVa
Problem ID: 490
Problem Title: Rotating Sentences
Problem Link: https://onlinejudge.org/external/4/490.pdf
Week: 2
Date: 2026/03/03
Theme: Strings, formatting
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12_490.cpp`

## 2. Problem Statement in My Own Words

* 這題會輸入很多行文字，要把整段文字順時針旋轉 90 度後輸出。

### What is the input?

* 輸入有多行字串。
* 每一行長度不一定一樣。
* 要一直讀到 EOF 為止。

### What is the expected output?

* 輸出旋轉 90 度後的文字。
* 原本最下面那一行會變成輸出時最左邊的字。
* 如果某一行比較短，旋轉後缺的位置要補空白。

### What are the main rules or constraints?

* 要保留空白，所以讀取時要用 `getline`。
* 每一行長度可能不同，所以要先找出最長的長度。
* 輸出時要從第 0 欄開始，依序輸出每一欄。
* 每一欄要從最後一行往第一行印。
* 如果某一行沒有那個位置的字元，就輸出空白。

### What is the core task you must solve?

* 核心任務是把多行字串當成二維字元資料，然後用欄和列的順序轉換，達到順時針旋轉 90 度的效果。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想法是把所有輸入的行先存起來，因為要旋轉的時候會需要從最後一行開始往上印。
* 這題比較麻煩的是每一行長度不一樣，不能直接當成完整的矩形處理。
* 所以需要記錄最長的那一行有多長，輸出時才知道總共要印幾列。

### Final Strategy

* 用字串陣列 `s[110]` 存下每一行輸入。
* 讀入時順便更新 `max_len`，記錄最長行的長度。
* 輸出時外層迴圈控制欄位 `i`，從 `0` 到 `max_len - 1`。
* 內層迴圈從最後一行 `n - 1` 跑回第 0 行。
* 如果目前這一行長度不夠，也就是 `i >= s[j].size()`，就印空白。
* 否則就印出 `s[j][i]`。

這樣做就等於把原本的文字順時針轉 90 度。

What edge cases did you consider?

* 每一行長度不同
* 某些位置沒有字元時要補空白
* 輸入中可能有空白，所以要用 `getline`
* 要從最後一行往第一行輸出
* 空字串或很短的行也要能處理

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. Set n = 0 and max_len = 0.
2. While input has a line:
3.     Store the line into s[n].
4.     Update max_len if this line is longer.
5.     Increase n by 1.
6. For i from 0 to max_len - 1:
7.     For j from n - 1 down to 0:
8.         If i is greater than or equal to the length of s[j]:
9.             Print a space.
10.        Else:
11.            Print s[j][i].
12.    Print newline.
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

using namespace std;

//  B

int main()
{
    string s[110];
    int n = 0;
    int max_len = 0;

    while ( getline( cin,s[n]) )
    {
        if ( s[n].size() > max_len )
        {
            max_len = s[n].size();
        }
        n++;
    }
    for ( int i = 0; i < max_len; i++ )
    {
        for ( int j = n - 1; j >= 0; j-- )
        {
            if ( i >= s[j].size() )
            {
                cout << " ";
            }
            else
            {
                cout << s[j][i];
            }
        }
        cout << endl;
    }
    return 0;
}
```

Why it works:

* 這份程式先把所有輸入行存進陣列，因為旋轉輸出時需要從最後一行往上印。
* `max_len` 可以決定旋轉後總共要輸出幾行。
* 外層迴圈代表原本字串的第幾個位置。
* 內層迴圈從最後一行跑到第一行，所以可以達成順時針旋轉的效果。
* 如果某一行沒有目前這個位置，就輸出空白，避免格式跑掉。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                 |
| --------------- | ----------------- | ---------------------------- |
| Logic           | 可能直接逐行輸出，沒有轉換列和欄。 | 用外層控制欄位、內層從最後一行往上印。          |
| Edge Cases      | 可能沒處理不同長度的行。      | 如果字串太短，就補空白。                 |
| Output Handling | 可能沒有保留空白或換行。      | 使用 `getline` 讀整行，並在每一列結束後換行。 |
| Other           | 可能沒有記錄最大長度。       | 用 `max_len` 控制輸出行數。          |

### Reflection

這題主要是在練習把字串當成二維陣列處理。
一開始比較容易搞混的是輸出方向，因為旋轉 90 度後要從最後一行開始印。

遇到這種旋轉題時，可以先想清楚「新的第幾行」對應到「原本的第幾欄」。
字串長度不同時一定要補空白，不然輸出格式就會錯。


