# UVa 732 - Anagrams by Stack

## 1. Problem Information

Platform: UVa
Problem ID: 732
Problem Title: Anagrams by Stack
Problem Link: https://onlinejudge.org/external/7/732.pdf
Week: 10
Date: 2026/04/28
Theme: Stack
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/732.cpp`

## 2. Problem Statement in My Own Words

* 這題會給兩個字串，第一個是原始字串，第二個是目標字串。我要用 stack 的 push 和 pop 操作，找出所有可以把原始字串轉成目標字串的操作順序。

### What is the input?

* 輸入有多組資料。
* 每組資料有兩個字串：

  * `sourceWord`
  * `targetWord`
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 每組資料要先輸出：

```text
[
```

* 接著輸出所有可行的操作順序。
* `i` 代表 push 進 stack。
* `o` 代表從 stack pop 出來。
* 每個操作之間要用空格隔開。
* 最後輸出：

```text
]
```

### What are the main rules or constraints?

* `i` 代表把 sourceWord 下一個字元 push 到 stack。
* `o` 代表把 stack top pop 出來，形成輸出字串的一個字元。
* pop 出來的字元必須符合 targetWord 目前需要的字元。
* 如果兩個字串長度不同，或字母組成不同，就不可能轉換。
* 需要列出所有可行操作。

### What is the core task you must solve?

* 用 DFS/backtracking 模擬所有 push 和 pop 的可能，並輸出能成功產生 targetWord 的操作序列。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到這題，感覺不能只用一般 stack 模擬一次，因為可能有很多種 push/pop 順序。
* 所以需要用遞迴去嘗試不同選擇。
* 每一步可能可以做 `i`，也可能可以做 `o`，只要符合條件就繼續往下走。

### Final Strategy

* 先檢查兩個字串長度是否相同，字母組成是否相同。
* 如果不相同，就沒有任何操作序列，只輸出空的中括號。
* 如果可能轉換，就用 DFS。
* DFS 中記錄：

  * source 目前讀到哪裡
  * target 目前完成到哪裡
  * 目前 stack 內容
  * 目前操作序列
* 如果 source 還有字元，就可以嘗試 push，也就是操作 `i`。
* 如果 stack 不空，而且 stack top 等於 target 目前需要的字元，就可以嘗試 pop，也就是操作 `o`。
* 當 target 全部完成時，就輸出目前操作序列。

What edge cases did you consider?

* 兩個字串長度不同
* 兩個字串字母組成不同
* stack 是空的時不能 pop
* stack top 不等於 target 目前字元時不能 pop
* 可能有多組輸入
* 每組輸出都要包在 `[` 和 `]` 中間

## 4. Pseudocode

```text
START
1. While input has sourceWord and targetWord:
2.     Print "[".
3.     If sourceWord and targetWord have the same length and same letters:
4.         Clear operations.
5.         Call DFS(sourceIndex = 0, targetIndex = 0, empty stack).
6.     Print "]".

DFS(sourceIndex, targetIndex, stack):
1. If targetIndex equals word length:
2.     Print operations.
3.     Return.
4. If sourceIndex is less than word length:
5.     Push sourceWord[sourceIndex] into stack.
6.     Add operation 'i'.
7.     Call DFS(sourceIndex + 1, targetIndex, stack).
8.     Undo operation 'i'.
9. If stack is not empty and stack.top equals targetWord[targetIndex]:
10.    Pop stack.
11.    Add operation 'o'.
12.    Call DFS(sourceIndex, targetIndex + 1, stack).
13.    Undo operation 'o'.
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
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// B Bonus

string sourceWord, targetWord;
vector<char> operations;

void dfs(int sourceIndex, int targetIndex, stack<char> st)
{
    int n = sourceWord.size();

    if (targetIndex == n)
    {
        for (int i = 0; i < operations.size(); i++)
        {
            if (i > 0)
            {
                cout << " ";
            }
            cout << operations[i];
        }
        cout << endl;
        return;
    }

    // push operation: take next character from sourceWord
    if (sourceIndex < n)
    {
        st.push(sourceWord[sourceIndex]);
        operations.push_back('i');

        dfs(sourceIndex + 1, targetIndex, st);

        operations.pop_back();
        st.pop();
    }

    // pop operation: stack top must match targetWord[targetIndex]
    if (!st.empty() && st.top() == targetWord[targetIndex])
    {
        char topChar = st.top();
        st.pop();
        operations.push_back('o');

        dfs(sourceIndex, targetIndex + 1, st);

        operations.pop_back();
        st.push(topChar);
    }
}

int main()
{
    while (cin >> sourceWord >> targetWord)
    {
        cout << "[" << endl;

        string a = sourceWord;
        string b = targetWord;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if (sourceWord.size() == targetWord.size() && a == b)
        {
            stack<char> st;
            operations.clear();

            dfs(0, 0, st);
        }

        cout << "]" << endl;
    }

    return 0;
}
```

Why it works:

* 程式先確認兩個字串長度和字母組成是否相同，避免不可能的情況。
* DFS 會嘗試所有合法的 push 和 pop 操作。
* push 時會把 sourceWord 下一個字元放進 stack。
* pop 時會先檢查 stack top 是否等於 targetWord 目前需要的字元。
* 每次遞迴後都會還原 operations 和 stack 狀態，所以可以繼續嘗試其他路線。
* 當 targetWord 全部完成時，就輸出目前的操作序列。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code                             |
| --------------- | --------------- | ---------------------------------------- |
| Logic           | 可能只模擬一種操作順序。    | 使用 DFS/backtracking 找出所有可行順序。            |
| Edge Cases      | 可能字串不可能轉換時還繼續跑。 | 先檢查長度和字母組成。                              |
| Output Handling | 可能忘記中括號或空格格式。   | 每組輸出用 `[` 和 `]` 包起來，操作間用空格。              |
| Other           | 可能遞迴後沒有還原狀態。    | 每次遞迴後都 pop_back 或 push 回去做 backtracking。 |

### Reflection

我學到如果題目要列出所有可能順序，通常不能只模擬一次，而是要用 DFS 去嘗試所有合法選擇。

這題最重要的是 pop 的條件。
不是 stack 有東西就可以 pop，而是 stack top 必須等於 target 目前需要的字元。
