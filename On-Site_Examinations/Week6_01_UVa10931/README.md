# UVa 10931 - Parity

## 1. Problem Information

Platform: UVa
Problem ID: 10931
Problem Title: Parity
Problem Link: https://onlinejudge.org/external/109/10931.pdf
Week: 6
Date: 2026/03/31
Theme: Median / order statistics
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/28_10931.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個十進位整數 `n`，我要把它轉成二進位，並計算二進位裡面有幾個 `1`。

### What is the input?

* 輸入有多筆整數。
* 每筆輸入是一個正整數 `n`。
* 當 `n = 0` 時，代表輸入結束，不需要輸出。

### What is the expected output?

* 對每個 `n`，輸出它的二進位表示法，以及裡面 `1` 的數量。
* 輸出格式是：

```text
The parity of binary is count (mod 2).
```

其中 `binary` 是二進位字串，`count` 是二進位中 `1` 的個數。

### What are the main rules or constraints?

* 要把十進位數字轉成二進位。
* 二進位中的 `1` 要計數。
* 輸入 `0` 時停止。
* 二進位輸出不能是反的，所以轉完後要反轉字串。

### What is the core task you must solve?

* 用除以 2 的方式轉二進位，同時統計餘數為 1 的次數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想到十進位轉二進位可以用一直除以 2 的方法。
* 每次 `n % 2` 就是目前最低位元。
* 如果這個 bit 是 1，就把 `count` 加 1。
* 只是這樣得到的二進位順序會是反的，所以最後要反轉字串。

### Final Strategy

* 每次讀入 `n`。
* 如果 `n == 0`，就結束。
* 設定 `count = 0` 來記錄有幾個 1。
* 設定字串 `s` 來存二進位。
* 當 `n > 0`：

  * `bit = n % 2`
  * 如果 `bit == 1`，`count++`
  * 把 bit 轉成字元後加到字串裡
  * `n /= 2`
* 因為字串順序是反的，所以用 `reverse` 反轉。
* 最後照題目格式輸出。

What edge cases did you consider?

* 輸入 `0` 時要停止，不輸出
* 二進位轉換順序要反過來
* `n` 本身是 1 的情況
* `n` 是 2 的次方時，二進位只有一個 1
* 輸出格式要完全符合題目

## 4. Pseudocode

```text
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Set count = 0.
5.     Set binary string s = empty.
6.     While n > 0:
7.         bit = n % 2.
8.         If bit == 1:
9.             Add 1 to count.
10.        Add bit as a character to s.
11.        n = n / 2.
12.    Reverse s.
13.    Print "The parity of s is count (mod 2)."
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
#include <algorithm>
#include <string>

using namespace std;

//  A

int main()
{
    int n;
    while ( cin >> n )
    {
        if ( n == 0 )   break;

        int count = 0;
        string s = "";                          // 字串 用來放二進位的數字
        while ( n > 0 )
        {
            int bit = n % 2;
            if ( bit == 1 )
            {
                count++;
            }
            s += char( bit + '0' );            // 轉二進位 但是還不是正確排序 要反過來
            n /= 2;
        }
        reverse ( s.begin() , s.end() );       // 反轉字串

        cout << "The parity of " << s << " is " << count << " (mod 2)." << endl;
    }
    return 0;
}
```

Why it works:

* 程式會讀到 `0` 才停止，符合題目輸入規則。
* 用 `n % 2` 取得目前二進位的最低位。
* 每次 bit 是 1 時，就把 `count` 加 1。
* 因為轉換出來的字串順序是反的，所以最後用 `reverse` 轉回正確順序。
* 最後輸出二進位字串和 `1` 的數量。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code              |
| --------------- | --------------- | ------------------------- |
| Logic           | 可能只轉二進位，沒有統計 1。 | 轉二進位時同時計算 bit 為 1 的數量。    |
| Edge Cases      | 可能忘記 `0` 是結束條件。 | 遇到 `0` 直接 break。          |
| Output Handling | 可能二進位輸出是反的。     | 使用 `reverse()` 把字串轉回正確順序。 |
| Other           | 可能輸出格式不符合題目。    | 照題目格式輸出完整句子。              |

### Reflection

這題主要是十進位轉二進位。
我覺得最容易錯的是用 `% 2` 得到的順序會是從低位到高位，所以最後要反轉。

