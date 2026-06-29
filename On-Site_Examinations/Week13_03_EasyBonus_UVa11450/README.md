# UVa 11450 - Wedding Shopping

## 1. Problem Information

Platform: UVa
Problem ID: 11450
Problem Title: Wedding Shopping
Problem Link: https://onlinejudge.org/external/114/11450.pdf
Week: 13
Date: 2026/05/19
Theme: Dynamic Programming
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11450.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一筆預算，還有好幾種衣服。每一種衣服都有不同 model 和價格，而且每一種衣服一定要選一件。我要在不超過預算的情況下，找出最多可以花多少錢。

### What is the input?

* 第一行是一個整數 `testCase`，代表有幾組測資。
* 每組測資先輸入兩個整數：

  * `money`：預算
  * `garmentCount`：衣服種類數量
* 接著每一種衣服會輸入：

  * 該衣服有幾個 model
  * 每個 model 的價格

### What is the expected output?

* 如果可以成功每種衣服都買一件，輸出最大花費。
* 如果沒有任何方法可以買齊所有種類，就輸出：

```text
no solution
```

### What are the main rules or constraints?

* 每一種衣服都必須選一個 model。
* 總花費不能超過預算。
* 目標是讓總花費越接近預算越好。
* 如果所有組合都超過預算，就沒有解。

### What is the core task you must solve?

* 用 DP 記錄每一階段可以達成的花費，最後找出不超過預算的最大值。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果用暴力法，把每種衣服的 model 全部組合都試過，可能會太多。
* 這題比較像 knapsack 類型，但限制是每一種衣服一定要選一個。
* 所以可以用 DP 來記錄「買完前幾種衣服後，哪些花費是可行的」。

### Final Strategy

* 先讀入預算 `money` 和衣服種類數 `garmentCount`。
* 用 `vector<vector<int>> garments` 存每種衣服的 model 價格。
* 建立 DP 表：

```text 
dp[i][spent] = true
```

代表買完前 `i` 種衣服後，剛好花 `spent` 元是可行的。

* 初始狀態：

```text 
dp[0][0] = true
```

代表還沒買任何衣服時，花費 0 元是可行的。

* 接著逐種衣服處理：

  * 如果 `dp[i][spent]` 是 true
  * 就嘗試選第 `i` 種衣服的每一個 model
  * 新花費是 `spent + price`
  * 如果沒有超過預算，就設成可行：

```text 
dp[i + 1][newSpent] = true
```

* 最後從 `money` 往下找第一個可行的 `spent`。
* 找得到就輸出該金額，找不到就輸出 `no solution`。

What edge cases did you consider?

* 所有組合都超過預算
* 剛好花完全部預算
* 每種衣服只有一個 model
* 有很多種衣服都要選
* `dp[garmentCount][spent]` 才代表所有衣服都買完
* 最後要從預算往下找最大可行值

## 4. Pseudocode

```text 
START
1. Read testCase.
2. Repeat testCase times:
3.     Read money and garmentCount.
4.     Read all garment model prices.
5.     Create dp table with false.
6.     Set dp[0][0] = true.
7.     For each garment i:
8.         For spent from 0 to money:
9.             If dp[i][spent] is true:
10.                For each price in garment i:
11.                    newSpent = spent + price.
12.                    If newSpent <= money:
13.                        dp[i + 1][newSpent] = true.
14.    Set answer = -1.
15.    For spent from money down to 0:
16.        If dp[garmentCount][spent] is true:
17.            answer = spent.
18.            Break.
19.    If answer == -1:
20.        Print "no solution".
21.    Else:
22.        Print answer.
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

using namespace std;

// A Bonus

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int money, garmentCount;
        cin >> money >> garmentCount;

        vector<vector<int>> garments(garmentCount);

        for (int i = 0; i < garmentCount; i++)
        {
            int modelCount;
            cin >> modelCount;

            for (int j = 0; j < modelCount; j++)
            {
                int price;
                cin >> price;
                garments[i].push_back(price);
            }
        }

        vector<vector<bool>> dp(garmentCount + 1, vector<bool>(money + 1, false));

        dp[0][0] = true;

        for (int i = 0; i < garmentCount; i++)
        {
            for (int spent = 0; spent <= money; spent++)
            {
                if (dp[i][spent])
                {
                    for (int j = 0; j < garments[i].size(); j++)
                    {
                        int newSpent = spent + garments[i][j];

                        if (newSpent <= money)
                        {
                            dp[i + 1][newSpent] = true;
                        }
                    }
                }
            }
        }

        int answer = -1;

        for (int spent = money; spent >= 0; spent--)
        {
            if (dp[garmentCount][spent])
            {
                answer = spent;
                break;
            }
        }

        if (answer == -1)
        {
            cout << "no solution" << endl;
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

* `dp[i][spent]` 可以記錄買完前 `i` 種衣服後，花費 `spent` 是否可行。
* 每次處理一種衣服時，都會嘗試該衣服所有 model 的價格。
* 因為轉移到 `dp[i + 1]`，所以可以確保每一種衣服都剛好選一件。
* `newSpent <= money` 可以避免超過預算。
* 最後從 `money` 往下找第一個可行花費，就能找到最大花費。
* 如果沒有任何可行花費，就輸出 `no solution`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code     | Correct Code            |
| --------------- | ------------- | ----------------------- |
| Logic           | 可能暴力枚舉所有衣服組合。 | 使用 DP 記錄可行花費。           |
| Edge Cases      | 可能沒有處理無解情況。   | 找不到答案時輸出 `no solution`。 |
| Output Handling | 可能找最小花費或錯誤花費。 | 從預算往下找最大可行花費。           |
| Other           | 可能沒有確保每種衣服都選。 | 每一層 DP 都代表多買完一種衣服。      |

### Reflection

這裡每一種衣服都一定要選一件，所以 DP 的層數很重要。

我覺得這題最關鍵的是 `dp[i][spent]` 的定義。
只要定義清楚，轉移就會變得比較直覺。
