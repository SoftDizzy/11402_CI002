# UVa 12207 - That is Your Queue

## 1. Problem Information

Platform: UVa
Problem ID: 12207
Problem Title: That is Your Queue
Problem Link: https://onlinejudge.org/external/122/12207.pdf
Week: 11
Date: 2026/05/05
Theme: Queue
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12207.cpp`

## 2. Problem Statement in My Own Words

* 這題是在模擬一個排隊系統。一開始有 `P` 個人，編號從 `1` 到 `P`。接著會有 `C` 個指令，每次根據指令改變隊伍順序或輸出目前被叫到的人。

### What is the input?

* 輸入有多組資料。
* 每組資料先輸入兩個整數 `P` 和 `C`。

  * `P` 代表總共有幾個人。
  * `C` 代表有幾個指令。
* 如果 `P = 0` 且 `C = 0`，代表輸入結束。
* 接下來有 `C` 個指令：

  * `N`
  * `E x`

### What is the expected output?

* 每組資料先輸出：

```text id="x3q9ii"
Case x:
```

* 如果指令是 `N`，要輸出目前隊伍最前面的人。

### What are the main rules or constraints?

* `N`：隊伍最前面的人被叫到，要輸出他的編號，然後他會回到隊伍最後面。
* `E x`：編號 `x` 的人有急事，要被移到隊伍最前面。
* 如果 `x` 原本已經在隊伍中，要先把他從原位置移除，再放到最前面。
* `P` 可能很大，所以不能直接把所有人都放進 queue。

### What is the core task you must solve?

* 用 `deque` 模擬可以從前面取出、從後面放回、也可以把指定的人移到最前面的隊伍。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到 `N` 指令，感覺可以用 queue，因為要從前面拿人，再放到後面。
* 但是 `E x` 需要把指定的人移到最前面，普通 queue 不方便刪除中間的人。
* 所以改用 `deque`，可以操作前後端，也可以用 iterator 找到指定的人後刪掉。

### Final Strategy

* 每次讀入 `P` 和 `C`。
* 如果 `P == 0 && C == 0`，結束程式。
* 建立一個 `deque<int>`。
* 因為最多只會執行 `C` 次指令，所以一開始不用放 `1` 到 `P` 全部的人。
* 只需要先放 `1` 到 `min(P, C)`。
* 如果指令是 `N`：

  * 取出 deque 最前面的人。
  * 輸出他。
  * 再把他放到 deque 最後面。
* 如果指令是 `E x`：

  * 先在 deque 中找有沒有 `x`。
  * 如果有，就把原本位置的 `x` 刪掉。
  * 再把 `x` 放到 deque 最前面。

What edge cases did you consider?

* `P = 0` 且 `C = 0` 時要停止
* `P` 很大，不能全部放進 deque
* `E x` 的 `x` 可能已經在 deque 裡
* `E x` 的 `x` 也可能不在目前 deque 裡
* `N` 之後被叫到的人要回到隊伍最後面
* Case 編號要從 1 開始

## 4. Pseudocode

```text 
START
1. Set cases = 1.
2. While input has P and C:
3.     If P == 0 and C == 0:
4.         Stop the program.
5.     Create an empty deque q.
6.     Set limit = min(P, C).
7.     Push numbers 1 to limit into q.
8.     Print "Case cases:".
9.     Repeat C times:
10.        Read command.
11.        If command is 'N':
12.            person = q.front().
13.            Pop front.
14.            Push person to back.
15.            Print person.
16.        Else if command is 'E':
17.            Read person.
18.            Search person in q.
19.            If found:
20.                Erase person from q.
21.            Push person to front.
22.    Increase cases by 1.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

### Correct Code

```cpp id="q3zbaa"
#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

// A Bonus

int main()
{
    int P, C;
    int cases = 1;

    while (cin >> P >> C)
    {
        if (P == 0 && C == 0)
        {
            break;
        }

        deque<int> q;

        int limit = min(P, C);

        for (int i = 1; i <= limit; i++)
        {
            q.push_back(i);
        }

        cout << "Case " << cases << ":" << endl;

        for (int i = 0; i < C; i++)
        {
            char command;
            cin >> command;

            if (command == 'N')
            {
                int person = q.front();
                q.pop_front();
                q.push_back(person);

                cout << person << endl;
            }
            else if (command == 'E')
            {
                int person;
                cin >> person;

                for (deque<int>::iterator it = q.begin(); it != q.end(); it++)
                {
                    if (*it == person)
                    {
                        q.erase(it);
                        break;
                    }
                }

                q.push_front(person);
            }
        }

        cases++;
    }

    return 0;
}
```

Why it works:

* `deque` 可以從前面取出，也可以從後面加入，符合 `N` 指令的需求。
* `deque` 也可以用 iterator 找到指定的人並刪除，方便處理 `E x`。
* 一開始只放 `min(P, C)` 個人，可以避免 `P` 很大時浪費記憶體和時間。
* `N` 指令會正確輸出隊伍最前面的人，並把他移到最後面。
* `E x` 指令會先移除原本的 `x`，再把他放到最前面，避免同一個人重複出現在隊伍中。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code               | Correct Code                   |
| --------------- | ----------------------- | ------------------------------ |
| Logic           | 可能用普通 queue，難以處理 `E x`。 | 使用 deque，可以移除中間元素並 push_front。 |
| Edge Cases      | 可能把 `P` 個人全部放進去。        | 只放 `min(P, C)` 個人，避免 P 太大。     |
| Output Handling | 可能 Case 格式錯。            | 正確輸出 `Case x:`。                |
| Other           | 可能讓同一個人重複出現。            | `E x` 時會先刪除原位置，再放到最前面。         |

### Reflection

因為有 `E x` 這個指令，所以不能只用一般 queue。
使用 `deque` 會比較方便，因為它可以從前後端操作，也能刪除中間找到的人。

我也學到有些題目的數字範圍很大時，不一定要真的建立全部資料。
這題最多只會操作 `C` 次，所以先放 `min(P, C)` 個人就夠了。

