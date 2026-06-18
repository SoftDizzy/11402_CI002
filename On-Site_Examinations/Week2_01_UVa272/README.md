# UVa 272 - TEX Quotes

## 1. Problem Information

Platform: UVa
Problem ID: 272
Problem Title: TEX Quotes
Problem Link: https://onlinejudge.org/external/2/272.pdf
Week: 2
Date: 2026/03/03
Theme: Strings, formatting
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/13_272.cpp`

## 2. Problem Statement in My Own Words

* 這題會給很多行文字，文字中可能會出現雙引號 `"`。我要把文章中的雙引號依序轉換成 TEX 格式的開引號和閉引號。

### What is the input?

* 輸入有很多行文字。
* 每一行可能包含一般字元、空白、標點符號或雙引號。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 輸出轉換後的文字。
* 第一個出現的 `"` 要轉成兩個反引號：

```text
``
```

* 第二個出現的 `"` 要轉成兩個單引號：

```text
''
```

* 之後的雙引號也依照開引號、閉引號、開引號、閉引號的順序交替轉換。
* 其他不是雙引號的字元要原樣輸出。

### What are the main rules or constraints?

* 要逐行讀取完整字串，不能只用 `cin >> s`，因為這樣會忽略空白。
* 需要使用 `getline(cin, s)` 才能保留整行內容。
* 開引號和閉引號是依照整份輸入的雙引號出現順序判斷，不是每一行重新開始。
* 遇到第一個 `"` 輸出 ````。
* 遇到第二個 `"` 輸出 `''`。
* 其他字元照原本內容輸出。

### What is the core task you must solve?

* 核心任務是逐字掃描輸入文字，遇到雙引號時根據目前狀態輸出 TEX 格式的開引號或閉引號，並在每次處理雙引號後切換狀態。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始的想法是，這題不需要複雜的演算法，只需要處理字串中的字元替換。
* 但是不能把所有 `"` 都換成同一個符號，因為奇數次出現的是開引號，偶數次出現的是閉引號。
* 所以需要一個變數記錄目前遇到的雙引號應該是開引號還是閉引號。

### Final Strategy

* 使用 `getline(cin, s)` 讀入每一整行文字。
* 使用一個布林變數 `a` 來記錄目前的雙引號狀態。
* 一開始 `a = true`，代表下一個遇到的雙引號是開引號。
* 當掃描到字元 `"`：

  * 如果 `a == true`，輸出 ````，並把 `a` 改成 `false`。
  * 如果 `a == false`，輸出 `''`，並把 `a` 改成 `true`。
* 如果不是雙引號，就直接輸出原本的字元。
* 每處理完一行後輸出換行。

這個方法可以正確解題，因為題目的雙引號一定是依照出現順序交替變成開引號和閉引號，所以只要用一個布林變數切換狀態即可。

What edge cases did you consider?

* 一行中有多組雙引號
* 某一行沒有任何雙引號
* 輸入有空白，所以要用 `getline`
* 開引號和閉引號的狀態要跨行保留
* 其他標點符號和文字不能被更改
* 每行輸出後要保留換行

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text
START
1. Set isOpeningQuote = true.
2. While input has a line s:
3.     For each character c in s:
4.         If c is a double quote:
5.             If isOpeningQuote is true:
6.                 Print two backticks.
7.                 Set isOpeningQuote = false.
8.             Else:
9.                 Print two single quotes.
10.                Set isOpeningQuote = true.
11.        Else:
12.            Print c.
13.    Print newline.
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


using namespace std;

// A

int main()
{
    string s;
    bool a = true;
    while ( getline ( cin , s ) )
    {

        for ( int i = 0; i < s.size(); i++ )
        {
            char c = s[i];
            if ( c == '"')
            {
                if ( a == true )
                {
                    cout << "``";
                    a = false;
                }
                else
                {
                    cout << "''";
                    a = true;
                }
            }
            else
                cout << c;

        }
        cout << endl;
    }
    return 0;
}
```

Why it works:

* 正確版本使用 `getline(cin, s)`，所以可以完整讀取包含空白的每一行文字。
* 變數 `a` 用來記錄下一個雙引號要輸出成開引號還是閉引號。
* 當遇到第一種狀態時，程式輸出 TEX 的開引號 ````。
* 當遇到另一種狀態時，程式輸出 TEX 的閉引號 `''`。
* 每處理一次雙引號，就切換 `a` 的狀態。
* 不是雙引號的字元會直接輸出，所以原本的文字內容不會被破壞。
* 因為 `a` 宣告在 `while` 迴圈外面，所以引號狀態可以跨行保留。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code               | Correct Code            |
| --------------- | ----------------------- | ----------------------- |
| Logic           | 可能把所有雙引號都換成同一種符號。       | 使用布林變數交替輸出開引號和閉引號。      |
| Edge Cases      | 可能忽略一行中多個雙引號或跨行引號狀態。    | 可以處理多個雙引號，也能保留跨行狀態。     |
| Output Handling | 可能使用 `cin >> s` 導致空白消失。 | 使用 `getline` 保留整行文字和空白。 |
| Other           | 可能忘記輸出換行或更動其他字元。        | 每行結束輸出換行，其他字元原樣輸出。      |

### Reflection

這題讓我學到，字串處理題不一定難在演算法，而是難在輸入輸出和格式細節。

我也學到如果題目要讀取整行文字，就應該使用 `getline`，不能只用 `cin >>`，不然空白會被切掉。

這題另一個重點是狀態紀錄。
因為開引號和閉引號是交替出現的，所以可以用一個 `bool` 變數記錄目前要輸出的類型。

如果之後再遇到類似的格式轉換題，我會先確認哪些字元需要被替換，哪些字元要保持原樣，並且注意狀態是否需要跨行保留。
