# UVa 673 - Parentheses Balance

## 1. Problem Information

Platform: UVa
Problem ID: 673
Problem Title: Parentheses Balance
Problem Link: https://onlinejudge.org/external/6/673.pdf
Week: 10
Date: 2026/04/28
Theme: Stack
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/673.cpp`

## 2. Problem Statement in My Own Words

* 這題會給多行括號字串，我要判斷每一行的括號是否有正確配對。括號包含小括號 `()` 和中括號 `[]`。

### What is the input?

* 第一行是一個整數，代表有幾組測資。
* 接下來每一行是一串括號字元。
* 可能會有空字串，所以要用 `getline` 讀整行。

### What is the expected output?

* 如果括號配對正確，輸出：

```text
Yes
```

* 如果括號配對錯誤，輸出：

```text
No
```

### What are the main rules or constraints?

* `(` 必須和 `)` 配對。
* `[` 必須和 `]` 配對。
* 括號順序也要正確，例如 `([)]` 是錯的。
* 遇到左括號時可以先存起來。
* 遇到右括號時要檢查最近的左括號是否對應。
* 最後 stack 必須是空的，才代表全部配對完成。

### What is the core task you must solve?

* 使用 stack 檢查括號的配對順序是否正確。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始想到括號配對很適合用 stack。
* 因為最新出現的左括號，必須最先被後面的右括號配對。
* 這剛好符合 stack 後進先出的特性。

### Final Strategy

* 先讀入測資數量 `testCase`。
* 因為後面要用 `getline`，所以先用 `cin.ignore()` 清掉換行。
* 每次讀入一整行字串。
* 遇到 `(` 或 `[` 時，就 push 進 stack。
* 遇到 `)` 時，檢查 stack 是否為空，或最上面是否不是 `(`。
* 遇到 `]` 時，檢查 stack 是否為空，或最上面是否不是 `[`。
* 如果不符合，就把 `ok` 設成 false。
* 最後如果 `ok == true` 且 stack 是空的，就輸出 `Yes`，否則輸出 `No`。

What edge cases did you consider?

* 空字串應該算平衡
* 只有左括號，例如 `((`
* 只有右括號，例如 `)]`
* 括號種類錯配，例如 `([)]`
* 讀完測資數量後要處理換行
* 最後 stack 沒清空代表還有左括號沒配對

## 4. Pseudocode

```text
START
1. Read testCase.
2. Ignore the newline after testCase.
3. Repeat for each test case:
4.     Read one line s.
5.     Create an empty stack.
6.     Set ok = true.
7.     For each character c in s:
8.         If c is '(' or '[':
9.             Push c into stack.
10.        Else if c is ')':
11.            If stack is empty or top is not '(':
12.                Set ok = false and stop checking this line.
13.            Else pop stack.
14.        Else if c is ']':
15.            If stack is empty or top is not '[':
16.                Set ok = false and stop checking this line.
17.            Else pop stack.
18.    If ok is true and stack is empty:
19.        Print Yes.
20.    Else:
21.        Print No.
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

using namespace std;

// A

int main()
{
    int testCase;
    cin >> testCase;
    cin.ignore();

    while (testCase--)
    {
        string s;
        getline(cin, s);

        stack<char> st;
        bool ok = true;

        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];

            if (c == '(' || c == '[')
            {
                st.push(c);
            }
            else if (c == ')')
            {
                if (st.empty() || st.top() != '(')
                {
                    ok = false;
                    break;
                }
                st.pop();
            }
            else if (c == ']')
            {
                if (st.empty() || st.top() != '[')
                {
                    ok = false;
                    break;
                }
                st.pop();
            }
        }

        if (ok && st.empty())
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式使用 stack 保存還沒配對的左括號。
* 遇到右括號時，會檢查 stack 最上面的左括號是否是對應種類。
* 如果 stack 是空的，代表沒有左括號可以配對，直接判斷錯誤。
* 如果最後 stack 是空的，代表所有左括號都有成功配對。
* 使用 `getline` 可以正確讀取每一整行括號字串。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code            | Correct Code                         |
| --------------- | -------------------- | ------------------------------------ |
| Logic           | 可能只計算括號數量。           | 使用 stack 檢查括號順序和種類。                  |
| Edge Cases      | 可能遇到右括號時 stack 為空會錯。 | 先檢查 `st.empty()` 再看 `top()`。         |
| Output Handling | 可能沒有處理空字串或換行。        | 用 `cin.ignore()` 和 `getline()` 正確讀取。 |
| Other           | 可能最後沒檢查剩餘左括號。        | 最後確認 `ok && st.empty()`。             |

### Reflection

這題是 stack 的基本題。
我學到括號配對不能只看數量一不一樣，還要看順序和種類。

像 `([)]` 這種例子，左右括號數量都對，但順序是錯的。
所以用 stack 會比較直覺，也比較安全。

