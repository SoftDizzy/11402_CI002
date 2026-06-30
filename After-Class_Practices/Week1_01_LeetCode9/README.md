# LeetCode 9 - Palindrome Number

## 1. Problem Information

Platform: LeetCode
Problem ID: 9
Problem Title: Palindrome Number
Problem Link: https://leetcode.com/problems/palindrome-number/
Week: 1
Date: 2026/02/24
Theme: I/O, EOF, absolute difference / After-Class Practice
Category: After-Class Practice
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/9.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個整數 `x`，要判斷它是不是 palindrome number。
* Palindrome number 的意思是從左讀到右，和從右讀到左都一樣。
* 例如 `121` 是 palindrome，但 `123` 不是。

### What is the input?

* 在 LeetCode 原題中，輸入是一個整數 `x`。
* 在我放進 repo 的版本中，用 `while (cin >> x)` 讀取多筆測試資料，方便自己用終端機測試。

### What is the expected output?

* 在 LeetCode 原題中，回傳 `true` 或 `false`。
* 在我的測試版本中：

  * 如果是 palindrome，輸出 `true`
  * 如果不是 palindrome，輸出 `false`

### What are the main rules or constraints?

* 負數不是 palindrome，因為前面有負號。
* 如果數字最後一位是 `0`，但數字本身不是 `0`，也不會是 palindrome。
* 不需要把整個數字反轉，因為可能有溢位風險。
* 可以只反轉數字的後半段，再跟前半段比較。

### What is the core task you must solve?

* 判斷整數從前面看和從後面看是否相同。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以把整個數字轉成字串，然後用左右雙指標比較。
* 但這份 code 使用數學方式處理，不轉成字串。
* 為了避免整個數字反轉後可能超過 int 範圍，只反轉後半段數字。

### Final Strategy

* 如果 `x < 0`，直接回傳 false。
* 如果 `x` 不是 0，但最後一位是 0，也直接回傳 false。
* 建立 `reversedHalf`，用來存反轉後的後半段。
* 當 `x > reversedHalf` 時，代表還沒處理到一半：

  * 把 `x` 的最後一位加到 `reversedHalf`
  * `x` 去掉最後一位
* 迴圈結束後：

  * 如果原本是偶數位數，檢查 `x == reversedHalf`
  * 如果原本是奇數位數，中間那位不用管，檢查 `x == reversedHalf / 10`

What edge cases did you consider?

* 負數，例如 `-121`
* 數字是 `0`
* 最後一位是 0，例如 `10`
* 偶數位 palindrome，例如 `1221`
* 奇數位 palindrome，例如 `121`
* 一般不是 palindrome 的數字，例如 `123`

## 4. Pseudocode


```text
START
1. Define function isPalindrome(x).
2. If x < 0:
3.     Return false.
4. If x is not 0 and x % 10 == 0:
5.     Return false.
6. Set reversedHalf = 0.
7. While x > reversedHalf:
8.     reversedHalf = reversedHalf * 10 + x % 10.
9.     x = x / 10.
10. If x == reversedHalf or x == reversedHalf / 10:
11.     Return true.
12. Else:
13.     Return false.
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

using namespace std;

// After-Class Practice
// LeetCode 9 - Palindrome Number

class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
        {
            return false;
        }

        if (x != 0 && x % 10 == 0)
        {
            return false;
        }

        int reversedHalf = 0;

        while (x > reversedHalf)
        {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        return x == reversedHalf || x == reversedHalf / 10;
    }
};

int main()
{
    Solution sol;

    int x;

    while (cin >> x)
    {
        if (sol.isPalindrome(x))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }

    return 0;
}
```

Why it works:

* 負數直接排除，因為負號不可能對稱。
* 最後一位是 0 的非零數字也直接排除，因為開頭不可能是 0。
* 程式只反轉後半段數字，不需要反轉完整整數。
* 偶數位數時，前半段會等於反轉後半段。
* 奇數位數時，`reversedHalf / 10` 可以去掉中間那位，再跟前半段比較。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code              | Correct Code              |
| --------------- | ---------------------- | ------------------------- |
| Logic           | 可能反轉整個數字。              | 只反轉後半段數字。                 |
| Edge Cases      | 可能負數或尾數 0 判斷錯。         | 先處理 `x < 0` 和尾數 0。        |
| Output Handling | 可能只適合 LeetCode，不能本機測試。 | 加上 `main()`，可以用終端機測試多筆資料。 |
| Other           | 可能有整數溢位風險。             | 不反轉完整數字，降低溢位問題。           |

### Reflection

這題是簡單的數字處理題，但還是有一些細節要注意。
我原本可能會想直接把整個數字反轉，但這樣有溢位風險。

只反轉後半段的做法比較安全，也比較有效率。
這題讓我練習到用 `% 10` 取最後一位，以及用 `/ 10` 去掉最後一位。