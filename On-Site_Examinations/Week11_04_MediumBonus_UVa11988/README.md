# UVa 11988 - Broken Keyboard

## 1. Problem Information

Platform: UVa
Problem ID: 11988
Problem Title: Broken Keyboard
Problem Link: https://onlinejudge.org/external/119/11988.pdf
Week: 11
Date: 2026/05/05
Theme: Queue / List
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11988.cpp`

## 2. Problem Statement in My Own Words

* 這題是在模擬壞掉的鍵盤。輸入文字中，如果遇到 `[`，游標會跑到最前面；如果遇到 `]`，游標會跑到最後面。其他一般字元就插入在目前游標位置。

### What is the input?

* 輸入有多行文字。
* 每一行都是一組測資。
* 要一直讀到 EOF 為止。

### What is the expected output?

* 對每一行輸入，輸出修正後的文字。
* `[` 和 `]` 本身不會出現在最後輸出裡。

### What are the main rules or constraints?

* `[`：游標移到文字最前面。
* `]`：游標移到文字最後面。
* 一般字元：插入在目前游標位置。
* 輸入可能很長，所以不能一直用 string 在前面插入，會太慢。

### What is the core task you must solve?

* 用可以快速插入的資料結構，模擬游標在文字前後移動並插入字元。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到 `[` 和 `]` 會改變輸入位置，我想到這題不是單純把字串照順序印出來。
* 如果用 `string.insert()` 一直在前面插入，資料長時可能會很慢。
* 所以可以用 `list<char>`，因為 list 可以在 iterator 指到的位置插入字元。

### Final Strategy

* 每次用 `getline` 讀入一整行。
* 建立一個 `list<char> text` 來存結果。
* 建立 iterator `cursor`，一開始指向 `text.end()`。
* 逐字元掃描輸入：

  * 如果是 `[`，就讓 cursor 指到 `text.begin()`。
  * 如果是 `]`，就讓 cursor 指到 `text.end()`。
  * 否則把字元插入 cursor 目前位置。
* 掃描完後，從 list 開頭到結尾輸出。

What edge cases did you consider?

* 一行中可能有多個 `[` 和 `]`
* `[` 可能出現在一開始
* `]` 可能出現在一開始
* 文字可能全部都在前面插入
* 輸入有多行，要讀到 EOF
* `[` 和 `]` 不可以輸出

## 4. Pseudocode

```text
START
1. While getline can read a line:
2.     Create an empty list text.
3.     Set cursor = text.end().
4.     For each character c in line:
5.         If c == '[':
6.             cursor = text.begin().
7.         Else if c == ']':
8.             cursor = text.end().
9.         Else:
10.            Insert c before cursor.
11.    Print all characters in text from begin to end.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

### Correct Code

```cpp id="o5q3tq"
#include <iostream>
#include <string>
#include <list>

using namespace std;

// B Bonus

int main()
{
    string line;

    while (getline(cin, line))
    {
        list<char> text;
        list<char>::iterator cursor = text.end();

        for (int i = 0; i < line.size(); i++)
        {
            char c = line[i];

            if (c == '[')
            {
                cursor = text.begin();
            }
            else if (c == ']')
            {
                cursor = text.end();
            }
            else
            {
                text.insert(cursor, c);
            }
        }

        for (list<char>::iterator it = text.begin(); it != text.end(); it++)
        {
            cout << *it;
        }

        cout << endl;
    }

    return 0;
}
```

Why it works:

* `list<char>` 可以在 iterator 指定的位置插入字元。
* 遇到 `[` 時，cursor 會移到文字最前面。
* 遇到 `]` 時，cursor 會移到文字最後面。
* 一般字元會插入在目前 cursor 的位置。
* 最後照 list 的順序輸出，就是修正後的文字。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code              |
| --------------- | ------------------ | ------------------------- |
| Logic           | 可能直接照原字串輸出。        | 使用 cursor 模擬插入位置。         |
| Edge Cases      | 可能沒有處理多個 `[`、`]`。  | 每遇到一次就更新 cursor。          |
| Output Handling | 可能把 `[`、`]` 印出來。   | `[`、`]` 只用來改變 cursor，不輸出。 |
| Other           | 可能用 string 前插導致很慢。 | 使用 list 在指定位置插入。          |

### Reflection

如果只用一般字串硬插入，會比較麻煩，也可能因為資料長度太長而變慢。

我學到遇到需要在中間或前面一直插入的問題時，可以考慮 `list`。
這題也提醒我，符號本身不一定是輸出內容，有時候只是控制游標或狀態。
