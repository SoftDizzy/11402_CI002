# UVa 12405 - Scarecrow

## 1. Problem Information

Platform: UVa
Problem ID: 12405
Problem Title: Scarecrow
Problem Link: https://onlinejudge.org/external/124/12405.pdf
Week: 15
Date: 2026/06/02
Theme: Greedy
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12405.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一排農地，`.` 代表需要被保護的位置，`#` 代表不用管的位置。
* 一個 scarecrow 可以保護連續三格。
* 我要用最少數量的 scarecrow，保護所有 `.` 的位置。

### What is the input?

* 第一行是一個整數 `testCase`，代表有幾組測資。
* 每組測資會輸入：

  * 一個整數 `n`，代表農地長度
  * 一個字串 `field`，代表農地狀態

### What is the expected output?

* 每組測資輸出：

```text 
Case x: answer
```

其中 `answer` 是最少需要的 scarecrow 數量。

### What are the main rules or constraints?

* `.` 代表需要被保護。
* `#` 代表不用保護。
* 一個 scarecrow 可以保護三格。
* 從左到右處理時，如果遇到還沒被保護的 `.`，就需要放一個 scarecrow。
* 放完之後可以跳過接下來兩格。

### What is the core task you must solve?

* 用 greedy 從左到右掃描，遇到需要保護的位置就放 scarecrow，並跳過已經被保護的範圍。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以想到用模擬的方式檢查每一格有沒有被保護。
* 但其實可以更簡單。
* 從左到右看，遇到第一個 `.` 時，代表這格一定需要被保護。
* 最好的做法是放一個 scarecrow 讓它一次保護目前這格和後面兩格。

### Final Strategy

* 讀入測資數量。
* 每組讀入 `n` 和 `field`。
* 設定 `scarecrow = 0`。
* 從左到右掃描字串：

  * 如果 `field[i] == '.'`：

    * 代表這格需要保護。
    * `scarecrow++`
    * 因為一個 scarecrow 可以保護三格，所以 `i += 3`。
  * 如果 `field[i] == '#'`：

    * 這格不用管，直接 `i++`。
* 最後輸出 scarecrow 數量。

What edge cases did you consider?

* 全部都是 `#`
* 全部都是 `.`
* 最後剩下一格或兩格 `.`
* `.` 和 `#` 交錯出現
* 每組測資都要輸出 Case 編號
* `i += 3` 可能超過字串長度，但迴圈條件會停止

## 4. Pseudocode

```text 
START
1. Read testCase.
2. For cases from 1 to testCase:
3.     Read n and field.
4.     Set scarecrow = 0.
5.     Set i = 0.
6.     While i < n:
7.         If field[i] == '.':
8.             scarecrow++.
9.             i = i + 3.
10.        Else:
11.            i++.
12.    Print "Case cases: scarecrow".
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

Why it failed:

* No failed version was saved.

如果有失敗版本，這題常見錯誤可能是：

* 每看到一個 `.` 就放一個 scarecrow，沒有跳過已保護範圍
* 忘記 scarecrow 可以保護三格
* `Case x:` 輸出格式錯誤
* 沒有處理最後剩下一格或兩格的情況
* 遇到 `#` 時沒有正確往下一格移動

### Correct Code

```cpp
#include <iostream>
#include <string>

using namespace std;

// A

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 1; cases <= testCase; cases++)
    {
        int n;
        string field;

        cin >> n >> field;

        int scarecrow = 0;

        for (int i = 0; i < n; )
        {
            if (field[i] == '.')
            {
                scarecrow++;
                i += 3;
            }
            else
            {
                i++;
            }
        }

        cout << "Case " << cases << ": " << scarecrow << endl;
    }

    return 0;
}
```

Why it works:

* 程式從左到右掃描農地。
* 遇到 `.` 時，代表目前位置需要被保護，所以一定要放 scarecrow。
* 放一個 scarecrow 後，可以保護目前位置和後面兩格，因此直接 `i += 3`。
* 遇到 `#` 時不用放 scarecrow，只要往下一格檢查。
* 這樣可以用最少數量覆蓋所有需要保護的格子。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                | Correct Code            |
| --------------- | ------------------------ | ----------------------- |
| Logic           | 可能每個 `.` 都放一個 scarecrow。 | 放一個後直接跳過三格。             |
| Edge Cases      | 可能最後幾格處理錯。               | 只要遇到 `.` 就加一，超出範圍由迴圈停止。 |
| Output Handling | 可能格式少了 Case。             | 正確輸出 `Case x: answer`。  |
| Other           | 可能沒有用 greedy。            | 從左到右遇到第一個未保護的 `.` 就放。   |

### Reflection

我覺得重點是不要想太複雜，只要從左到右處理第一個還沒被保護的 `.`。

因為這個 `.` 一定要被保護，所以直接放一個 scarecrow，並讓它盡量保護後面的格子。
這樣每一步都做目前最合理的選擇，最後就可以得到最少數量。

