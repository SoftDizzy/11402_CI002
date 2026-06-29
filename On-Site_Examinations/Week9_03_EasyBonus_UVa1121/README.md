# UVa 1121 - Subsequence

## 1. Problem Information

Platform: UVa
Problem ID: 1121
Problem Title: Subsequence
Problem Link: https://onlinejudge.org/external/11/1121.pdf
Week: 9
Date: 2026/04/21
Theme: Prefix sums / difference arrays
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/1121.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一串正整數和一個目標值 `s`，我要找出最短的連續子序列，使它的總和大於或等於 `s`。

### What is the input?

* 輸入有多組資料。
* 每組資料先輸入兩個整數 `n` 和 `s`。

  * `n` 是數列長度。
  * `s` 是目標總和。
* 接著輸入 `n` 個正整數。

### What is the expected output?

* 輸出最短連續子序列的長度。
* 如果沒有任何一段連續子序列總和可以達到 `s`，就輸出 `0`。
* 每組答案輸出一行。

### What are the main rules or constraints?

* 子序列必須是連續的。
* 總和要大於或等於 `s`。
* 要找的是最短長度。
* 數列中的數字都是正整數，所以可以用 sliding window。
* 輸入要讀到 EOF。

### What is the core task you must solve?

* 用兩個指標維持一段連續區間，找出總和達到 `s` 的最短長度。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以用雙層迴圈枚舉所有區間，但這樣會比較慢。
* 因為題目中的數字都是正數，所以當右邊界往右移時，總和只會變大。
* 當總和已經大於等於 `s` 時，就可以嘗試把左邊界往右移，看看能不能縮短長度。

### Final Strategy

* 用 `left` 和 `right` 表示目前視窗範圍。
* `right` 每次往右加入一個數字，讓 `sum` 增加。
* 當 `sum >= s` 時，代表目前區間符合條件。
* 此時更新最短長度，然後把 `left` 的數字移出視窗，繼續嘗試縮短。
* 如果最後沒有找到符合條件的區間，就輸出 `0`。

What edge cases did you consider?

* 沒有任何區間總和達到 `s`
* 單一元素就大於或等於 `s`
* 最短答案在中間，不一定從開頭開始
* 有多組輸入，要讀到 EOF
* 因為都是正數，所以 sliding window 才適用

## 4. Pseudocode

```text id="ym5d4b"
START
1. While input has n and s:
2.     Read n numbers into vector v.
3.     Set left = 0.
4.     Set sum = 0.
5.     Set answer = infinity.
6.     For right from 0 to n - 1:
7.         Add v[right] to sum.
8.         While sum >= s:
9.             length = right - left + 1.
10.            Update answer with smaller length.
11.            Subtract v[left] from sum.
12.            Move left to the right.
13.    If answer is still infinity:
14.        Print 0.
15.    Else:
16.        Print answer.
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
#include <vector>
#include <climits>

using namespace std;

// A Bonus

int main()
{
    int n, s;

    while (cin >> n >> s)
    {
        vector<int> v(n);

        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        int left = 0;
        int sum = 0;
        int answer = INT_MAX;

        for (int right = 0; right < n; right++)
        {
            sum += v[right];

            while (sum >= s)
            {
                int length = right - left + 1;

                if (length < answer)
                {
                    answer = length;
                }

                sum -= v[left];
                left++;
            }
        }

        if (answer == INT_MAX)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << answer << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式使用 `left` 和 `right` 維持目前的連續區間。
* `right` 往右移時，把新數字加入 `sum`。
* 當 `sum >= s` 時，代表目前區間符合條件，就更新最短長度。
* 接著移動 `left`，嘗試縮短區間。
* 因為數字都是正數，所以這樣移動視窗不會漏掉答案。
* 如果最後沒有找到任何符合條件的區間，就輸出 `0`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code              | Correct Code              |
| --------------- | ---------------------- | ------------------------- |
| Logic           | 可能枚舉所有區間。              | 使用 sliding window 維持連續區間。 |
| Edge Cases      | 可能沒處理找不到答案。            | 如果 `answer` 沒更新，就輸出 `0`。  |
| Output Handling | 可能只找到第一個可行區間就停止。       | 持續縮短視窗，找最短長度。             |
| Other           | 可能把 subsequence 當成不連續。 | 這題處理的是連續區間。               |

### Reflection

因為所有數字都是正數，所以右邊界往右會讓總和變大，左邊界往右會讓總和變小。

我覺得最容易錯的是找到一個符合條件的區間後就停下來。
其實還要繼續移動 `left`，看看能不能找到更短的長度。

