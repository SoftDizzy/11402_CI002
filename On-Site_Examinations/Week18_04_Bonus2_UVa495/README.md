# UVa 495 - Fibonacci Freeze

## 1. Problem Information

Platform: UVa
Problem ID: 495
Problem Title: Fibonacci Freeze
Problem Link: https://onlinejudge.org/external/4/495.pdf
Week: 18
Date: Not specified
Theme: Dynamic Programming / Big Integer
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/495.cpp`

## 2. Problem Statement in My Own Words

* 這題要計算第 `n` 個 Fibonacci number。
* 一般 Fibonacci 的公式是 `F(n) = F(n - 1) + F(n - 2)`。
* 但是這題的 `n` 可以很大，答案會超過 `long long`，所以不能用一般整數存。
* 因此要用字串來做大數加法。

### What is the input?

* 輸入有多組資料。
* 每組資料是一個整數 `n`。
* 要一直讀到 EOF 為止。

### What is the expected output?

* 對每個 `n`，輸出：

```text 
The Fibonacci number for n is answer
```

其中 `answer` 是第 `n` 個 Fibonacci number。

### What are the main rules or constraints?

* `F(0) = 0`
* `F(1) = 1`
* `F(n) = F(n - 1) + F(n - 2)`
* 因為答案很大，所以要用 Big Integer 的方式處理。
* C++ 沒有內建 Big Integer，所以用 `string` 自己做加法。

### What is the core task you must solve?

* 先用 DP 預先算出 Fibonacci 數列，並用字串大數加法避免溢位。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以直接用 Fibonacci 的公式計算。
* 但是如果用 `int` 或 `long long`，算到比較大的 `n` 就會溢位。
* 所以這題不能只靠普通數字型別。
* 需要把每個 Fibonacci number 當成字串存起來，然後自己寫加法。

### Final Strategy

* 建立 `vector<string> fib(5001)`。
* 設定初始值：

```text 
fib[0] = "0"
fib[1] = "1"
```

* 從 `2` 算到 `5000`：

```text
fib[i] = fib[i - 1] + fib[i - 2]
```

* 因為是字串，所以使用 `addString()` 函式來做大數加法。
* `addString()` 從兩個字串的最後一位開始加，並處理 carry。
* 預先算好後，每次輸入 `n`，直接輸出 `fib[n]`。

What edge cases did you consider?

* `n = 0`
* `n = 1`
* `n` 很大時答案超過 `long long`
* 多組輸入要讀到 EOF
* 大數加法要處理進位 carry
* 輸出格式必須完全符合題目要求

## 4. Pseudocode

```text
START
1. Define addString(a, b):
2.     Set result = empty string.
3.     Set carry = 0.
4.     Start from the last digit of a and b.
5.     While there are digits left or carry exists:
6.         Add current digits and carry.
7.         Push the last digit of sum into result.
8.         Update carry.
9.     Reverse result.
10.    Return result.

11. Create fib array of string with size 5001.
12. Set fib[0] = "0".
13. Set fib[1] = "1".
14. For i from 2 to 5000:
15.     fib[i] = addString(fib[i - 1], fib[i - 2]).
16. While input has n:
17.     Print "The Fibonacci number for n is fib[n]".
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
#include <algorithm>

using namespace std;

// B Bonus

string addString(string a, string b)
{
    string result = "";
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;

        if (i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }

        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    vector<string> fib(5001);

    fib[0] = "0";
    fib[1] = "1";

    for (int i = 2; i <= 5000; i++)
    {
        fib[i] = addString(fib[i - 1], fib[i - 2]);
    }

    int n;

    while (cin >> n)
    {
        cout << "The Fibonacci number for " << n << " is " << fib[n] << endl;
    }

    return 0;
}
```

Why it works:

* `fib[i]` 用字串保存第 `i` 個 Fibonacci number，所以不會受到整數範圍限制。
* `addString()` 可以模擬手算加法，從個位數開始加，並處理進位。
* Fibonacci 的轉移式是 `fib[i] = fib[i - 1] + fib[i - 2]`。
* 程式先預先算好 `0` 到 `5000` 的答案。
* 讀入每個 `n` 後直接查表輸出，效率很穩定。
* 輸出格式符合題目要求的句子。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code             | Correct Code                      |
| --------------- | --------------------- | --------------------------------- |
| Logic           | 可能用一般整數直接算 Fibonacci。 | 使用 string 儲存大數。                   |
| Edge Cases      | 可能大數溢位。               | 用 `addString()` 做 Big Integer 加法。 |
| Output Handling | 可能只輸出答案數字。            | 輸出完整句子格式。                         |
| Other           | 可能每次輸入才重新計算。          | 預先算好後直接查表。                        |

### Reflection

如果用 `long long`，很快就會超過範圍，所以要改用字串處理大數。

我覺得這題可以順便練習 Big Integer 加法。
做法就是從字串最後一位開始加，像手算一樣處理 carry，最後再把結果反轉回來。

