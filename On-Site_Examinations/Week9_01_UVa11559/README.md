# UVa 11559 - Event Planning

## 1. Problem Information

Platform: UVa
Problem ID: 11559
Problem Title: Event Planning
Problem Link: https://onlinejudge.org/external/115/11559.pdf
Week: 9
Date: 2026/04/21
Theme: Prefix sums / difference arrays
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11559.cpp`

## 2. Problem Statement in My Own Words

* 這題要幫一群人找飯店。題目會給人數、預算、飯店數量和可選週數，我要找出有足夠床位而且價格不超過預算的最便宜方案。

### What is the input?

* 輸入有多組資料。
* 每組資料先輸入四個整數 `n b h w`。

  * `n` 是參加人數。
  * `b` 是總預算。
  * `h` 是飯店數量。
  * `w` 是可選週數。
* 接著每間飯店會先給每人價格 `price`。
* 再給 `w` 個整數，代表每一週可用床位數。

### What is the expected output?

* 如果有飯店符合條件，就輸出最小總花費。
* 如果沒有任何飯店符合條件，就輸出：

```text
stay home
```

### What are the main rules or constraints?

* 總花費是 `n * price`。
* 飯店必須至少有一週的床位數 `beds >= n`。
* 總花費不能超過預算 `b`。
* 要從所有可行飯店中找最便宜的價格。
* 輸入要讀到 EOF。

### What is the core task you must solve?

* 檢查每一間飯店是否有足夠床位且不超過預算，並記錄最小可行花費。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始我覺得這題就是把每間飯店都檢查一次。
* 每間飯店有一個固定價格，然後有很多週的床位數。
* 只要其中一週床位夠，就可以考慮這間飯店。

### Final Strategy

* 每組資料讀入 `n, b, h, w`。
* 設定 `best = b + 1`，代表目前還沒有找到可行答案。
* 對每一間飯店：

  * 讀入每人價格 `price`。
  * 檢查接下來 `w` 週是否有任一週 `beds >= n`。
  * 如果有足夠床位，就計算 `cost = n * price`。
  * 如果 `cost <= b`，就更新最小值 `best`。
* 最後如果 `best <= b`，輸出 `best`。
* 否則輸出 `stay home`。

What edge cases did you consider?

* 沒有任何飯店有足夠床位
* 有床位但超過預算
* 多間飯店都可行，要選最便宜的
* 某間飯店只要有一週床位夠就可以
* 有多組輸入，要讀到 EOF

## 4. Pseudocode

```text
START
1. While input has n, b, h, w:
2.     Set best = b + 1.
3.     Repeat h times:
4.         Read price.
5.         Set enoughBeds = false.
6.         Repeat w times:
7.             Read beds.
8.             If beds >= n:
9.                 Set enoughBeds = true.
10.        cost = n * price.
11.        If enoughBeds is true and cost <= b:
12.            best = minimum of best and cost.
13.    If best <= b:
14.        Print best.
15.    Else:
16.        Print "stay home".
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

using namespace std;

// A

int main()
{
    int n, b, h, w;

    while (cin >> n >> b >> h >> w)
    {
        int best = b + 1;

        for (int i = 0; i < h; i++)
        {
            int price;
            cin >> price;

            bool enoughBeds = false;

            for (int j = 0; j < w; j++)
            {
                int beds;
                cin >> beds;

                if (beds >= n)
                {
                    enoughBeds = true;
                }
            }

            int cost = n * price;

            if (enoughBeds && cost <= b)
            {
                best = min(best, cost);
            }
        }

        if (best <= b)
        {
            cout << best << endl;
        }
        else
        {
            cout << "stay home" << endl;
        }
    }

    return 0;
}
```

Why it works:

* 程式會讀到 EOF，可以處理多組資料。
* 每間飯店都會檢查所有週數，只要其中一週床位足夠就可以。
* `cost = n * price` 用來算總花費。
* 如果有床位且預算足夠，就用 `min()` 更新最便宜方案。
* 如果最後沒有任何可行方案，就輸出 `stay home`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code        |
| --------------- | --------------- | ------------------- |
| Logic           | 可能只檢查一間或一週。     | 檢查每間飯店的所有週數。        |
| Edge Cases      | 可能有床位但預算不夠也算進去。 | 同時檢查床位和預算。          |
| Output Handling | 可能大小寫或文字錯。      | 正確輸出 `stay home`。   |
| Other           | 可能沒有找最小花費。      | 用 `best` 記錄目前最便宜方案。 |

### Reflection

我覺得重點是要把「床位夠」和「預算夠」兩個條件分開檢查。

某間飯店只要有一週床位夠就可以，不是每一週都要夠。
下次遇到這種多條件篩選的題目，我會先把每個條件列出來，再一個一個判斷。
