# UVa 1062 - Containers

## 1. Problem Information

Platform: UVa
Problem ID: 1062
Problem Title: Containers
Problem Link: https://onlinejudge.org/external/10/1062.pdf
Week: 10
Date: 2026/04/28
Theme: Stack
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/1062.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一串 container 的字母順序，要把它們依序放到一些 stacks 裡，並求出最少需要幾個 stack。

### What is the input?

* 輸入有多組字串。
* 每組字串代表 container 的順序。
* 當輸入是 `end` 時，代表結束。

### What is the expected output?

* 每組資料要輸出：

```text
Case x: answer
```

其中 `x` 是 case 編號，`answer` 是最少需要的 stack 數量。

### What are the main rules or constraints?

* container 要按照輸入順序處理。
* 每個 container 可以放到某個 stack 的最上面。
* 如果某個 stack 最上面的字母大於或等於目前 container，就可以放上去。
* 如果沒有 stack 可以放，就要開一個新的 stack。
* 目標是讓 stack 數量越少越好。

### What is the core task you must solve?

* 用 greedy 的方式，盡量把目前 container 放到已經存在的 stack，最後得到最少 stack 數量。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始我想到可以用多個 stack 來模擬，但其實只需要記錄每個 stack 最上面的字母。
* 因為判斷能不能放，只跟 stack top 有關。
* 所以可以用 `vector<char>` 存每個 stack 目前最上面的 container。

### Final Strategy

* 每次讀入一個字串 `s`。
* 如果 `s == "end"`，就結束。
* 建立 `vector<char> stacks`。
* 依序處理字串中的每個字母。
* 對目前 container，從前面的 stack 開始找：

  * 如果 `stacks[j] >= container`，代表可以放到這個 stack。
  * 放上去後，這個 stack 的 top 變成目前 container。
* 如果所有 stack 都不能放，就新增一個 stack。
* 最後 `stacks.size()` 就是答案。

What edge cases did you consider?

* 輸入是 `end` 時要停止
* 每組都要重新建立 stacks
* container 字母可能是遞增，會需要比較多 stack
* container 字母可能是遞減，可以放在同一個 stack
* Case 編號要從 1 開始

## 4. Pseudocode

```text
START
1. Set cases = 1.
2. While input has string s:
3.     If s == "end":
4.         Stop the program.
5.     Create an empty vector stacks.
6.     For each container in s:
7.         Set placed = false.
8.         For each stack top in stacks:
9.             If stack top >= container:
10.                Replace stack top with container.
11.                Set placed = true.
12.                Stop searching.
13.        If placed is false:
14.            Add a new stack with this container.
15.    Print "Case cases: number of stacks".
16.    Increase cases by 1.
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
#include <vector>

using namespace std;

// A Bonus

int main()
{
    string s;
    int cases = 1;

    while (cin >> s)
    {
        if (s == "end")
        {
            break;
        }

        vector<char> stacks;

        for (int i = 0; i < s.size(); i++)
        {
            char container = s[i];
            bool placed = false;

            for (int j = 0; j < stacks.size(); j++)
            {
                if (stacks[j] >= container)
                {
                    stacks[j] = container;
                    placed = true;
                    break;
                }
            }

            if (!placed)
            {
                stacks.push_back(container);
            }
        }

        cout << "Case " << cases << ": " << stacks.size() << endl;
        cases++;
    }

    return 0;
}
```

Why it works:

* 程式每次只記錄每個 stack 最上面的 container。
* 如果某個 stack top 大於或等於目前 container，就可以把目前 container 放上去。
* 放上去後只需要更新該 stack 的 top。
* 如果找不到可以放的 stack，就新增一個 stack。
* 最後 stacks 的數量就是最少需要的 stack 數量。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                 | Correct Code            |
| --------------- | ------------------------- | ----------------------- |
| Logic           | 可能每個 container 都開新 stack。 | 優先找可以放的舊 stack。         |
| Edge Cases      | 可能忘記處理 `end`。             | 遇到 `end` 就停止。           |
| Output Handling | 可能 Case 格式錯。              | 輸出 `Case x: answer`。    |
| Other           | 可能存整個 stack。              | 只存每個 stack 的 top，判斷更簡單。 |

### Reflection

這題雖然主題是 stack，但實作時其實不用真的存每一堆的全部內容。
因為每次判斷只需要看最上面的 container，所以用 `vector<char>` 存 top 就夠了。

我學到 greedy 題常常是每一步都先找目前可以用的選擇。
這題就是先嘗試放到現有 stack，真的不行才開新的 stack。

