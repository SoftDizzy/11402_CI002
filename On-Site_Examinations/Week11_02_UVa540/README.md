# UVa 540 - Team Queue

## 1. Problem Information

Platform: UVa
Problem ID: 540
Problem Title: Team Queue
Problem Link: https://onlinejudge.org/external/5/540.pdf
Week: 11
Date: 2026/05/05
Theme: Queue
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/540.cpp`

## 2. Problem Statement in My Own Words

* 這題是模擬一個特殊的排隊系統。每個人都屬於某個 team，當同 team 的人已經在隊伍裡時，新來的人要排到自己 team 的最後面，而不是整個隊伍的最後面。

### What is the input?

* 輸入有多組 scenario。
* 每組先輸入 team 的數量。
* 如果 team 數量是 `0`，代表輸入結束。
* 接著輸入每個 team 有幾個成員，以及這些成員的編號。
* 後面會有多個指令：

  * `ENQUEUE x`：把成員 `x` 加入隊伍
  * `DEQUEUE`：輸出目前隊伍最前面的人，並把他移除
  * `STOP`：結束目前 scenario

### What is the expected output?

* 每組 scenario 要先輸出：

```text 
Scenario #x
```

* 每次遇到 `DEQUEUE`，輸出被移除的成員編號。
* 每個 scenario 結束後要輸出一個空行。

### What are the main rules or constraints?

* 同一個 team 的人要盡量排在一起。
* 如果某個 team 已經有人在排隊，新加入的同 team 成員要排在該 team 的最後。
* 如果該 team 目前沒有人在排隊，才把這個 team 加到整體隊伍後面。
* `STOP` 代表目前 scenario 結束。
* `teamCount = 0` 代表整個輸入結束。

### What is the core task you must solve?

* 用 queue 模擬整體 team 順序，並用每個 team 自己的 queue 保存該 team 成員順序。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果只用一個普通 queue，會很難處理同 team 插隊到同 team 後面的情況。
* 所以我想到要分成兩層來處理：

  * 一層記錄目前有哪些 team 正在排隊。
  * 一層記錄每個 team 裡面的成員順序。
* 這樣 `DEQUEUE` 時只要看目前最前面的 team，再從那個 team 的 queue 取出成員。

### Final Strategy

* 先用 `unordered_map<int, int>` 記錄每個 member 屬於哪個 team。
* 建立 `vector<queue<int>> teamQueues`，每一格代表一個 team 的成員 queue。
* 建立 `queue<int> teamOrder`，記錄目前正在排隊的 team 順序。
* 處理 `ENQUEUE x` 時：

  * 先查出 `x` 屬於哪個 team。
  * 如果該 team 的 queue 原本是空的，代表這個 team 還沒在總隊伍中，要把 team 加入 `teamOrder`。
  * 再把 `x` 加入該 team 的 queue。
* 處理 `DEQUEUE` 時：

  * 先看 `teamOrder.front()` 是哪個 team。
  * 輸出該 team queue 最前面的 member。
  * 把該 member pop 掉。
  * 如果該 team queue 變空，就把這個 team 從 `teamOrder` pop 掉。

What edge cases did you consider?

* team 數量是 `0` 時要結束整個程式
* `STOP` 時只結束目前 scenario
* 同一個 team 連續多人加入
* 某個 team 清空後，下次再有人加入時要重新進入 `teamOrder`
* 每個 scenario 結束後要輸出空行
* scenario 編號要從 1 開始增加

## 4. Pseudocode

```text
START
1. Set scenario = 1.
2. While input has teamCount:
3.     If teamCount == 0:
4.         Stop the program.
5.     Create memberTeam map.
6.     For each team:
7.         Read memberCount.
8.         Read each member and store memberTeam[member] = team index.
9.     Create teamQueues for all teams.
10.    Create teamOrder queue.
11.    Print scenario title.
12.    While input has command:
13.        If command is STOP:
14.            Stop current scenario.
15.        Else if command is ENQUEUE:
16.            Read member.
17.            Find the member's team.
18.            If that team's queue is empty:
19.                Push team into teamOrder.
20.            Push member into that team's queue.
21.        Else if command is DEQUEUE:
22.            team = teamOrder.front().
23.            Print front member of that team's queue.
24.            Pop that member.
25.            If that team's queue becomes empty:
26.                Pop teamOrder.
27.    Print blank line.
28.    Increase scenario.
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
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// B

int main()
{
    int teamCount;
    int scenario = 1;

    while (cin >> teamCount)
    {
        if (teamCount == 0)
        {
            break;
        }

        unordered_map<int, int> memberTeam;

        for (int i = 0; i < teamCount; i++)
        {
            int memberCount;
            cin >> memberCount;

            for (int j = 0; j < memberCount; j++)
            {
                int member;
                cin >> member;
                memberTeam[member] = i;
            }
        }

        vector<queue<int>> teamQueues(teamCount);
        queue<int> teamOrder;

        cout << "Scenario #" << scenario << endl;

        string command;

        while (cin >> command)
        {
            if (command == "STOP")
            {
                break;
            }
            else if (command == "ENQUEUE")
            {
                int member;
                cin >> member;

                int team = memberTeam[member];

                if (teamQueues[team].empty())
                {
                    teamOrder.push(team);
                }

                teamQueues[team].push(member);
            }
            else if (command == "DEQUEUE")
            {
                int team = teamOrder.front();

                cout << teamQueues[team].front() << endl;
                teamQueues[team].pop();

                if (teamQueues[team].empty())
                {
                    teamOrder.pop();
                }
            }
        }

        cout << endl;
        scenario++;
    }

    return 0;
}
```

Why it works:

* `memberTeam` 可以快速查出每個 member 屬於哪個 team。
* `teamQueues[i]` 保存第 `i` 個 team 目前正在排隊的成員。
* `teamOrder` 保存目前隊伍中 team 的先後順序。
* 當某個 team 第一次加入隊伍時，才會被放進 `teamOrder`。
* 同 team 的其他成員會直接加入自己的 team queue 後面，不會打亂整體 team 順序。
* `DEQUEUE` 時永遠從最前面的 team 取人，符合題目規則。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code              | Correct Code                     |
| --------------- | ---------------------- | -------------------------------- |
| Logic           | 可能只用單一 queue 排所有人。     | 使用 teamOrder 加上每個 team 的 queue。  |
| Edge Cases      | 可能 team 清空後沒有移除。       | team queue 變空時會 pop 掉 teamOrder。 |
| Output Handling | 可能少印 scenario 標題或空行。   | 每組輸出 `Scenario #x`，結束後印空行。       |
| Other           | 查 member 所屬 team 可能很慢。 | 使用 `unordered_map` 快速查詢。         |

### Reflection

把問題拆成「team 的順序」和「team 內部成員順序」後，邏輯就清楚很多。
這題讓我更理解有些模擬題不是只需要一個資料結構，而是要組合多個資料結構一起使用。
