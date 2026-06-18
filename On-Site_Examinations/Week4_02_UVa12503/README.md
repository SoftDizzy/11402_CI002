# UVa 12503 - Robot Instructions

## 1. Problem Information

Platform: UVa
Problem ID: 12503
Problem Title: Robot Instructions
Problem Link: https://onlinejudge.org/external/125/12503.pdf
Week: 4
Date: 2026/03/17
Theme: Arrays + simulation
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12503.cpp`

## 2. Problem Statement in My Own Words

* 這題有一個機器人，一開始位置在 `0`。題目會給很多指令，根據指令讓機器人往左或往右移動，最後輸出機器人的位置。

### What is the input?

* 第一行是一個整數，代表有幾組測資。
* 每組測資先給一個整數 `n`，代表有幾個指令。
* 接下來會有 `n` 行指令，可能是：

  * `LEFT`
  * `RIGHT`
  * `SAME AS x`

### What is the expected output?

* 每組測資輸出一個整數，代表機器人最後的位置。
* 每筆答案輸出一行。

### What are the main rules or constraints?

* `LEFT` 代表位置減 1。
* `RIGHT` 代表位置加 1。
* `SAME AS x` 代表這個指令要和第 `x` 個指令做一樣的移動。
* 指令的編號是從 1 開始。
* 程式中的陣列或 vector index 是從 0 開始，所以要注意 `x - 1`。

### What is the core task you must solve?

* 核心任務是模擬所有指令，並且記錄每一個指令實際造成的移動，這樣遇到 `SAME AS x` 時才能查回之前的指令。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到 `LEFT` 和 `RIGHT` 很簡單，直接讓位置加減 1 就好。
* 比較麻煩的是 `SAME AS x`，因為它不是新的方向，而是要照之前第 `x` 個指令做一樣的事情。
* 所以不能只記錄目前位置，還要記錄每一個指令真正造成的移動量。

### Final Strategy

* 用 `position` 記錄目前機器人的位置。
* 用 `vector<int> instructions` 存每個指令的移動量。
* 如果指令是 `LEFT`：

  * 存 `-1`
  * `position--`
* 如果指令是 `RIGHT`：

  * 存 `1`
  * `position++`
* 如果指令是 `SAME AS x`：

  * 找出 `instructions[x - 1]`
  * 把這個移動量存進 vector
  * `position` 加上這個移動量
* 全部指令處理完後輸出 `position`。

What edge cases did you consider?

* `SAME AS x` 的 `x` 是從 1 開始，不是從 0 開始
* `SAME AS x` 可能指到之前也是 `SAME AS` 的指令
* 有多組測資
* 每組測資的 `position` 和指令紀錄都要重新開始
* 最後位置可能是負數

## 4. Pseudocode

```text
START
1. Read testCase.
2. Repeat for each test case:
3.     Read n.
4.     Set position = 0.
5.     Create an empty list instructions.
6.     For each instruction:
7.         Read command.
8.         If command is LEFT:
9.             Add -1 to instructions.
10.            position = position - 1.
11.        Else if command is RIGHT:
12.            Add 1 to instructions.
13.            position = position + 1.
14.        Else:
15.            Read "AS" and index.
16.            move = instructions[index - 1].
17.            Add move to instructions.
18.            position = position + move.
19.    Print position.
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

using namespace std;

// B

int main()
{
    int testCase;
    cin >> testCase;

    while ( testCase-- )
    {
        int n;
        cin >> n;

        vector<int> instructions;
        int position = 0;

        for ( int i = 0; i < n; i++ )
        {
            string command;
            cin >> command;

            if ( command == "LEFT" )
            {
                instructions.push_back(-1);
                position--;
            }
            else if ( command == "RIGHT" )
            {
                instructions.push_back(1);
                position++;
            }
            else
            {
                string asText;
                int index;
                cin >> asText >> index;

                int move = instructions[index - 1];
                instructions.push_back(move);
                position += move;
            }
        }

        cout << position << endl;
    }

    return 0;
}
```

Why it works:

* 程式會先讀取測資數量，每一組都重新建立 `instructions` 和 `position`。
* `LEFT` 和 `RIGHT` 直接轉成移動量 `-1` 和 `1`。
* 遇到 `SAME AS x` 時，程式會去找第 `x` 個指令的移動量。
* 因為 vector 是從 0 開始，所以使用 `index - 1`。
* 每一個 `SAME AS` 本身也會被存入 `instructions`，所以後面的指令也可以參考它。
* 最後輸出 `position`，就是機器人最後的位置。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                  | Correct Code                          |
| --------------- | -------------------------- | ------------------------------------- |
| Logic           | 可能只處理 `LEFT` 和 `RIGHT`。    | 把每個指令轉成移動量並存起來。                       |
| Edge Cases      | 可能沒處理 `SAME AS x` 指到之前的指令。 | 使用 `instructions[index - 1]` 找回之前的移動。 |
| Output Handling | 可能沒有每組測資都重新輸出結果。           | 每組測資處理完就輸出一次位置。                       |
| Other           | 可能忘記 vector 是 0-based。     | `SAME AS x` 使用 `x - 1` 取得正確指令。        |

### Reflection

這題的重點是 `SAME AS x`。
如果只記錄現在的位置，會不知道第 `x` 個指令原本做了什麼，所以一定要把每個指令的移動量存起來。

