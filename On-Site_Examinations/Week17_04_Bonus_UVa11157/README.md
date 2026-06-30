# UVa 11157 - Dynamic Frog

## 1. Problem Information

Platform: UVa
Problem ID: 11157
Problem Title: Dynamic Frog
Problem Link: https://onlinejudge.org/external/111/11157.pdf
Week: 17
Date: Not specified
Theme: Greedy / Simulation
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11157.cpp`

## 2. Problem Statement in My Own Words

* 這題有一隻青蛙要從河的左岸跳到右岸，再從右岸跳回左岸。
* 河上有 big stones 和 small stones。
* Big stone 可以踩很多次，small stone 只能踩一次，踩過就不能再踩。
* 我要找出一種跳法，讓整趟來回過程中的最大跳躍距離最小。

### What is the input?

* 第一行是一個整數 `testCase`，代表有幾組測資。
* 每組測資先輸入兩個整數：

  * `n`：石頭數量
  * `d`：河的寬度
* 接著輸入 `n` 個石頭資料，例如：

```text 
B-10
S-15
```

* `B` 代表 big stone。
* `S` 代表 small stone。
* 數字代表石頭的位置。

### What is the expected output?

* 每組測資輸出：

```text 
Case x: answer
```

其中 `answer` 是青蛙來回過程中最小可能的最大跳躍距離。

### What are the main rules or constraints?

* 起點是 `0`。
* 終點是 `d`。
* Big stone 可以踩很多次，所以去程和回程都可以踩。
* Small stone 只能踩一次，所以不能去程踩完回程又踩。
* 目標不是總距離最短，而是讓最大單次跳躍距離最小。

### What is the core task you must solve?

* 用 greedy 的想法，把 big stone 視為可重複使用，small stone 視為只能使用一次，最後計算最小化後的最大跳躍距離。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果真的模擬青蛙去程和回程，會比較難處理 small stone 被踩掉的狀況。
* 但觀察後可以發現，small stone 只能用一次，所以去程和回程會像是交錯使用石頭。
* Big stone 可以重複踩，所以可以把它當成出現兩次。
* 起點和終點也可以來回都使用，所以也放兩次。

### Final Strategy

* 先建立一個 `stones` vector。
* 把起點 `0` 放兩次。
* 讀入每個石頭：

  * 如果是 big stone，就把它的位置放兩次。
  * 如果是 small stone，就只放一次。
* 把終點 `d` 放兩次。
* 因為 stones 已經按照輸入位置順序排列，所以可以直接檢查。
* 來回交錯使用石頭時，最大跳躍距離可以用：

```text 
stones[i] - stones[i - 2]
```

* 從 `i = 2` 開始掃描整個 vector，取最大值。
* 這個最大值就是答案。

What edge cases did you consider?

* 沒有任何石頭
* 全部都是 big stones
* 全部都是 small stones
* 起點和終點要能來回使用，所以各放兩次
* small stone 只能出現一次
* 每組測資都要輸出 Case 編號

## 4. Pseudocode

```text 
START
1. Read testCase.
2. For cases from 1 to testCase:
3.     Read n and d.
4.     Create stones vector.
5.     Push 0 twice into stones.
6.     Repeat n times:
7.         Read stone string s.
8.         type = first character of s.
9.         position = number after "B-" or "S-".
10.        If type is 'B':
11.            Push position twice.
12.        Else:
13.            Push position once.
14.    Push d twice into stones.
15.    Set answer = 0.
16.    For i from 2 to stones size - 1:
17.        answer = max(answer, stones[i] - stones[i - 2]).
18.    Print "Case cases: answer".
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

Why it failed:

### Correct Code

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// B Bonus

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 1; cases <= testCase; cases++)
    {
        int n, d;
        cin >> n >> d;

        vector<int> stones;

        stones.push_back(0);
        stones.push_back(0);

        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;

            char type = s[0];
            int position = stoi(s.substr(2));

            if (type == 'B')
            {
                stones.push_back(position);
                stones.push_back(position);
            }
            else
            {
                stones.push_back(position);
            }
        }

        stones.push_back(d);
        stones.push_back(d);

        int answer = 0;

        for (int i = 2; i < stones.size(); i++)
        {
            answer = max(answer, stones[i] - stones[i - 2]);
        }

        cout << "Case " << cases << ": " << answer << endl;
    }

    return 0;
}
```

Why it works:

* Big stone 可以踩很多次，所以放兩次代表去程和回程都可以使用。
* Small stone 只能踩一次，所以只放一次。
* 起點和終點一定可以來回使用，所以也各放兩次。
* 當去程和回程交錯使用石頭時，實際可能的最大跳躍距離會出現在 `stones[i] - stones[i - 2]`。
* 掃描所有這種距離並取最大值，就能得到最小化後的最大跳躍距離。
* 最後按照題目要求輸出 `Case x: answer`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code            | Correct Code                              |
| --------------- | -------------------- | ----------------------------------------- |
| Logic           | 可能直接模擬去程和回程。         | 用石頭出現次數表示可使用次數。                           |
| Edge Cases      | 可能 small stone 被踩兩次。 | small stone 只放一次。                         |
| Output Handling | 可能格式錯誤。              | 正確輸出 `Case x: answer`。                    |
| Other           | 可能只看相鄰石頭距離。          | 使用 `stones[i] - stones[i - 2]` 考慮跳過石頭的情況。 |

### Reflection

Big stone 可以重複踩，所以放兩次；small stone 只能踩一次，所以只放一次。

我覺得最重要的是理解為什麼要看 `i` 和 `i - 2` 的距離。
因為青蛙來回時，small stone 可能已經被另一趟用掉，所以某一趟可能需要跳過中間那顆石頭。

