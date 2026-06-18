# UVa 10035 - Primary Arithmetic


## 1. Problem Information

Platform: UVa  
Problem ID: 10035  
Problem Title: Primary Arithmetic  
Problem Link: https://onlinejudge.org/external/100/10035.pdf  
Week: 1  
Date: 2026/02/24  
Theme: I/O, EOF, absolute difference  
Category: On-site Medium  
Source Code (Fail): No failed version was saved  
Source Code (Correct/Accepted): `src/3_10035.cpp`

## 2. Problem Statement in My Own Words

- 這題會給兩個非負整數，我要模擬直式加法，計算兩個數字相加時總共發生幾次進位 carry operation。

### What is the input?

- 輸入有很多組資料，每一組有兩個整數 a 和 b。
當輸入是 0 0 時，代表程式結束，不需要輸出結果。

### What is the expected output?

- 如果沒有任何進位，要輸出：
No carry operation.
- 如果只有一次進位，要輸出：
1 carry operation.
- 如果有兩次以上進位，要輸出：
x carry operations.
其中 x 是進位的次數。

### What are the main rules or constraints?

- 要從個位數開始一位一位相加。
- 每一位相加時，要加上前一位產生的進位。
- 如果某一位的總和大於等於 10，就會產生一次 carry operation。
- 產生進位後，下一位相加時要多加 1。
- 輸入 0 0 時停止。

### What is the core task you must solve?

- 核心任務是模擬兩個整數的直式加法，並計算整個加法過程中總共發生幾次進位。

## 3. Thinking Logic and Solution Strategy


### Initial Thoughts

- 我一開始的想法是，只要像直式加法一樣，從個位數開始檢查每一位有沒有進位即可。

這題一開始比較需要注意的是，進位會影響下一位的計算。
例如某一位相加後超過 10，下一位就要多加 1。
所以除了記錄進位次數，還需要一個變數記錄目前是否有 carry。

### Final Strategy

- 我使用 a % 10 和 b % 10 取出兩個數字目前的個位數。
- 再加上上一輪留下來的進位 k。
- 如果總和大於等於 10，就代表這一位會產生進位，進位次數 c 加一，並把 k 設成 1。
- 如果總和小於 10，就沒有進位，把 k 設成 0。
- 每次處理完一位後，使用 a /= 10 和 b /= 10 去掉已經處理過的個位數。
直到兩個數字都處理完為止。

What edge cases did you consider?

- 輸入是 0 0 時要結束，不輸出任何結果
- 沒有任何進位時，要輸出 No carry operation.
- 只有一次進位時，operation 要用單數
- 多次進位時，operations 要用複數
- 兩個數字位數不同時，較短的數字後面可以視為 0
- 連續進位的情況，例如 999 + 1

## 4. Pseudocode



```text
START
1. While input has two integers a and b: 
2. If a == 0 and b == 0: 
3. Stop the program. 
4. Set carryCount = 0. 
5. Set carry = 0. 
6. While a > 0 or b > 0: 
7. sum = last digit of a + last digit of b + carry. 
8. If sum >= 10: 
9. Add 1 to carryCount. 
10. Set carry = 1. 
11. Else: 
12. Set carry = 0. 
13. Remove the last digit of a. 
14. Remove the last digit of b. 
15. Print the result according to carryCount.
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

// A

int main()
{
    int a,b;
    while ( cin >> a >> b )
    {
        if ( a == 0 && b == 0 )  break;

        int c = 0;
        int k = 0;
        
        while ( a > 0 || b > 0 )
        {
            int sum = 0;
            sum = a % 10 + b % 10 + k;
            if ( sum >= 10 )
            {
                c++;
                k = 1;
            }
            else 
            {
                k = 0;
            }
            a /= 10;
            b /= 10;
        }

        if ( c == 0 )
        {
            cout << "No carry operation." << endl;
        }
        else if ( c == 1 )
        {
            cout << "1 carry operation." << endl;
        }
        else
        {
           cout << c << " carry operations." << endl;
        }
    }
}
```

Why it works:

- 正確版本可以持續讀取多組輸入，直到遇到 0 0 才結束。
- 程式使用 % 10 取出個位數，模擬直式加法從右到左相加的過程。
- 變數 k 用來記錄上一位是否有進位。
- 如果某一位的總和大於等於 10，就代表發生一次 carry operation，並讓下一位多加 1。
- 變數 c 會累計總共發生幾次進位。
- 最後根據 c 的值輸出不同格式，符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
|---|---|---|
| Logic | 可能只直接計算 a + b，沒有模擬每一位進位。 | 使用 % 10 和 / 10 一位一位模擬直式加法。 |
| Edge Cases | 可能忽略 0 0 結束條件或連續進位。 | 可以處理結束條件、不同位數和連續進位。 |
| Output Handling | 可能沒有分單數和複數輸出。 | 依照進位次數分成 0 次、1 次、多次輸出。 |
| Other | 可能沒有把 carry 傳到下一位。 | 使用 k 記錄上一位的 carry。 |

### Reflection

這題讓我學到，不是每一題都需要真的算出最後的數值答案。
有時候題目要的是計算過程中的某種狀態，例如這題要的是加法過程中發生幾次進位。

我也學到模擬直式加法時，可以用 % 10 取得最後一位，再用 / 10 去掉最後一位。
這種方法很適合處理數字的每一位。

如果之後再遇到類似題目，我會先想清楚題目是要「最後結果」還是「過程中的次數或狀態」。
我也會特別注意輸出格式，像這題的單數 operation 和複數 operations 就很容易寫錯。
