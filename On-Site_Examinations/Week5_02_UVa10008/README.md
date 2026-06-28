# UVa 10008 - What's Cryptanalysis?

## 1. Problem Information

Platform: UVa
Problem ID: 10008
Problem Title: What's Cryptanalysis?
Problem Link: https://onlinejudge.org/external/100/10008.pdf
Week: 5
Date: 2026/03/24
Theme: Sorting basics
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/8_10008.cpp`

## 2. Problem Statement in My Own Words

* 這題會給多行英文句子，我要統計每個英文字母出現幾次，不分大小寫，最後依照出現次數由多到少輸出。

### What is the input?

* 第一行是一個整數 `n`，代表接下來有幾行文字。
* 接著會有 `n` 行句子。
* 句子裡可能有大小寫英文字母、空白或其他符號。

### What is the expected output?

* 輸出每個有出現過的英文字母和它出現的次數。
* 次數多的字母要先輸出。
* 如果次數一樣，按照字母順序 `A` 到 `Z` 輸出。

### What are the main rules or constraints?

* 大寫和小寫要當成同一個字母。
* 只統計英文字母，其他符號和空白不用算。
* 輸出時字母要用大寫。
* 排序規則是先看出現次數，再看字母順序。

### What is the core task you must solve?

* 統計 `A` 到 `Z` 每個字母的出現次數，然後依照題目要求的順序輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想法是用一個大小為 26 的陣列來存每個字母出現的次數。
* 因為英文字母只有 26 個，所以不用用很複雜的資料結構。
* 比較要注意的是輸入有整行句子，所以讀完 `n` 之後要用 `cin.ignore()` 處理換行，後面才能正常 `getline`。

### Final Strategy

* 建立整數陣列 `a[26]`，用來記錄 `A` 到 `Z` 的次數。
* 讀入行數 `n` 後，用 `cin.ignore()` 清掉換行。
* 每次用 `getline` 讀一整行文字。
* 對每個字元檢查是不是英文字母。
* 如果是字母，就先轉成大寫，再用 `c - 'A'` 算出陣列位置。
* 每次統計時順便更新目前最大出現次數 `max_c`。
* 輸出時從 `max_c` 倒著跑到 1，內層再從 `A` 到 `Z` 檢查，這樣就可以做到次數由大到小、同次數照字母順序輸出。

What edge cases did you consider?

* 有大小寫混在一起
* 句子裡有空白或符號
* 字母出現次數一樣時要照 A 到 Z
* 讀完 `n` 之後要處理換行
* 沒出現的字母不用輸出

## 4. Pseudocode

```text
START
1. Read n.
2. Ignore the newline after n.
3. Create an array a[26] and set all values to 0.
4. Set max_c = 0.
5. Repeat n times:
6.     Read one whole line.
7.     For each character c in the line:
8.         If c is an alphabet letter:
9.             Convert c to uppercase.
10.            index = c - 'A'.
11.            Add 1 to a[index].
12.            Update max_c if needed.
13. For count from max_c down to 1:
14.     For each letter from A to Z:
15.         If this letter appears count times:
16.             Print the letter and count.
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
#include <cctype>

using namespace std;

// B

int main()
{
    int n;
    cin >> n;
    cin.ignore();
    int a[26] = {0};
    int max_c = 0;
    while ( n-- )
    {
        string line;
        getline( cin , line );

        for ( int i = 0; i < line.size(); i++ )
        {
            char c = line[i];
            if ( isalpha(c) )
            {
                c = toupper(c);
                int index = c - 'A';
                a[index]++;

                if ( a[index] > max_c )
                {
                    max_c = a[index];
                }
            }

        }

    }

    for ( int i = max_c; i > 0; i-- )
    {
        for ( int j = 0; j < 26; j++ )
        {
            if ( a[j] == i )
            {
                char z = 'A' + j;
                cout << z << " " << i << endl;
            }
        }
    }
    return 0;
}
```

Why it works:

* 程式用 `a[26]` 統計 26 個英文字母的出現次數。
* `isalpha(c)` 可以確認目前字元是不是英文字母。
* `toupper(c)` 讓大小寫可以一起計算。
* `max_c` 記錄最大出現次數，輸出時可以從最大值開始往下找。
* 內層迴圈從 `A` 到 `Z`，所以當次數一樣時會自動照字母順序輸出。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code                    |
| --------------- | ---------------- | ------------------------------- |
| Logic           | 可能沒有正確統計 26 個字母。 | 使用 `a[26]` 記錄每個字母出現次數。          |
| Edge Cases      | 可能把大小寫分開算。       | 使用 `toupper()` 統一成大寫。           |
| Output Handling | 可能沒有按照次數排序。      | 從 `max_c` 往下輸出，並用 A 到 Z 處理同次數。  |
| Other           | 可能忘記處理第一行後的換行。   | 使用 `cin.ignore()` 後再 `getline`。 |

### Reflection

這題主要是在練習字元統計和輸出順序。
我覺得最容易錯的是讀取輸入，因為第一行是數字，後面是整行句子，所以要記得先處理換行。

