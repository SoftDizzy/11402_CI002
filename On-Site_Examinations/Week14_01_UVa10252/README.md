# UVa 10252 - Common Permutation

## 1. Problem Information

Platform: UVa
Problem ID: 10252
Problem Title: Common Permutation
Problem Link: https://onlinejudge.org/external/102/10252.pdf
Week: 14
Date: 2026/05/26
Theme: Sorting / Frequency Counting
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11_10252.cpp`

## 2. Problem Statement in My Own Words

* 這題會給兩行小寫英文字串，要找出兩個字串共同擁有的字母，並且依照字母順序輸出。
* 如果某個字母在兩個字串中都出現，就輸出它們出現次數的較小值。

### What is the input?

* 輸入有多組資料。
* 每組資料有兩行字串：

  * 第一行是 `s1`
  * 第二行是 `s2`
* 要一直讀到 EOF 為止。

### What is the expected output?

* 對每組資料，輸出兩個字串共同的字母。
* 字母要按照 `a` 到 `z` 的順序輸出。
* 每組答案輸出一行。

### What are the main rules or constraints?

* 輸入字串只需要處理小寫英文字母。
* 同一個字母如果在兩個字串中都出現多次，要取較小的出現次數。
* 輸出結果要按照字母順序。
* 如果沒有共同字母，就輸出空行。

### What is the core task you must solve?

* 統計兩個字串每個字母出現次數，然後輸出共同出現的部分。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以想到把兩個字串排序後再慢慢比對。
* 但這份 code 用更直接的方式，統計每個字母的出現次數。
* 因為只有 26 個小寫字母，所以可以用兩個大小為 26 的陣列來記錄。

### Final Strategy

* 用 `getline` 一次讀兩行字串。
* 建立兩個陣列 `c1[26]` 和 `c2[26]`。
* 掃描 `s1`，把每個字母出現次數記錄到 `c1`。
* 掃描 `s2`，把每個字母出現次數記錄到 `c2`。
* 從 `a` 到 `z` 檢查每個字母。
* 對每個字母，取：

```text 
min(c1[i], c2[i])
```

* 這個值代表該字母在兩個字串中共同出現的次數。
* 最後依照共同次數輸出對應字母。

What edge cases did you consider?

* 兩個字串沒有共同字母
* 某個字母在其中一個字串出現很多次
* 字串可能是空字串
* 輸入有多組，要讀到 EOF
* 輸出要按照字母順序
* 每組答案最後都要換行

## 4. Pseudocode

```text 
START
1. While getline can read s1 and s2:
2.     Create c1[26] and c2[26], initialized to 0.
3.     For each character in s1:
4.         index = character - 'a'.
5.         c1[index]++.
6.     For each character in s2:
7.         index = character - 'a'.
8.         c2[index]++.
9.     For i from 0 to 25:
10.        same = min(c1[i], c2[i]).
11.        Repeat same times:
12.            Print character 'a' + i.
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
#include <cctype>
using namespace std;

//  A

int main()
{
    string s1,s2;


    while ( getline(cin,s1) && getline(cin,s2))
    {
        int c1[26]={0};
        int c2[26]={0};
        for ( int i = 0; i < s1.size(); i++ )
        {
            int index1 = s1[i] - 'a';
            c1[index1]++;
        }
        for ( int i = 0; i < s2.size(); i++ )
        {
            int index2 = s2[i] - 'a';
            c2[index2]++;
        }
        for ( int i = 0; i < 26; i++ )
        {
            int same = min( c1[i],c2[i] );
            for ( int j = 0; j < same; j++ )
            {
                char c = i + 'a';
                cout << c;
            }
        }
        cout << endl;
    }
    return 0;
}
```

Why it works:

* `c1[26]` 和 `c2[26]` 分別記錄兩個字串中每個字母的出現次數。
* `s1[i] - 'a'` 可以把字母轉成 `0` 到 `25` 的 index。
* 對每個字母取 `min(c1[i], c2[i])`，就能得到共同出現的次數。
* 從 `i = 0` 到 `25` 輸出，所以結果自然會按照 `a` 到 `z` 排序。
* 每組輸出後換行，符合題目格式。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code    | Correct Code                   |
| --------------- | ------------ | ------------------------------ |
| Logic           | 可能只檢查字母是否存在。 | 統計每個字母出現次數。                    |
| Edge Cases      | 可能重複字母處理錯。   | 使用 `min(c1[i], c2[i])` 決定共同次數。 |
| Output Handling | 可能沒有排序輸出。    | 從 `a` 到 `z` 依序輸出。              |
| Other           | 可能沒有讀完整一行。   | 使用 `getline` 讀兩個字串。            |

### Reflection

我覺得它比直接排序後比對更直覺，因為小寫字母只有 26 個，所以用陣列統計很方便。

這題也提醒我，共同字母不是只看有沒有出現，而是要看出現次數。
例如一邊有三個 `a`，另一邊只有一個 `a`，最後只能輸出一個 `a`。

