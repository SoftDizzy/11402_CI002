# UVa 10935 - Throwing cards away

## 1. Problem Information

Platform: UVa
Problem ID: 10935
Problem Title: Throwing cards away
Problem Link: https://onlinejudge.org/external/109/10935.pdf
Week: 11
Date: 2026/05/05
Theme: Queue
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10935.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一疊從 `1` 到 `n` 的牌。每次先丟掉最上面的牌，再把下一張牌移到牌堆底部，重複到只剩一張牌。我要輸出丟掉的牌和最後剩下的牌。

### What is the input?

* 輸入有多組資料。
* 每組資料是一個整數 `n`。
* 當 `n = 0` 時，代表輸入結束。

### What is the expected output?

* 每組資料要輸出兩行。
* 第一行輸出被丟掉的牌：

```text
Discarded cards: ...
```

* 第二行輸出最後剩下的牌：

```text
Remaining card: x
```

### What are the main rules or constraints?

* 牌一開始的順序是 `1, 2, 3, ..., n`。
* 每回合先丟掉最上面的牌。
* 接著把新的最上面那張牌移到牌堆底部。
* 重複直到只剩下一張牌。
* 丟掉的牌輸出時要用逗號分隔。
* 如果一開始只有一張牌，就沒有 discarded cards。

### What is the core task you must solve?

* 用 queue 模擬牌堆上方丟牌、移牌到底部的過程。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到題目要一直從最前面拿牌，又要把牌放到最後面，所以我想到用 queue。
* 因為 queue 可以從 front 取出元素，也可以用 push 把元素放到後面。
* 這剛好符合題目的牌堆操作。

### Final Strategy

* 每次讀入 `n`。
* 如果 `n == 0`，就結束。
* 建立一個 queue，把 `1` 到 `n` 依序放進去。
* 當 queue 裡面超過一張牌時：

  * 先取出 front，這張就是 discarded card。
  * 接著再取出新的 front，並把它 push 回 queue 後面。
* 最後 queue 裡剩下的一張就是 remaining card。
* 輸出 discarded cards 時用 `first` 控制逗號格式。

What edge cases did you consider?

* `n = 0` 時要停止
* `n = 1` 時沒有任何 discarded card
* 丟掉的牌中間要用 `, ` 分隔
* 最後剩下的牌要另外輸出
* 有多組輸入，要一直處理到 0

## 4. Pseudocode

```text
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Create an empty queue cards.
5.     Push numbers from 1 to n into cards.
6.     Print "Discarded cards:".
7.     Set first = true.
8.     While cards has more than one card:
9.         discarded = cards.front().
10.        Pop discarded card.
11.        Print discarded with correct comma format.
12.        moved = cards.front().
13.        Pop moved card.
14.        Push moved card to the back of queue.
15.    Print "Remaining card: " and cards.front().
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

using namespace std;

// A

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        queue<int> cards;

        for (int i = 1; i <= n; i++)
        {
            cards.push(i);
        }

        cout << "Discarded cards:";

        bool first = true;

        while (cards.size() > 1)
        {
            int discarded = cards.front();
            cards.pop();

            if (first)
            {
                cout << " " << discarded;
                first = false;
            }
            else
            {
                cout << ", " << discarded;
            }

            int moved = cards.front();
            cards.pop();
            cards.push(moved);
        }

        cout << endl;
        cout << "Remaining card: " << cards.front() << endl;
    }

    return 0;
}
```

Why it works:

* 程式用 queue 依序保存目前牌堆。
* `front()` 可以取得最上面的牌，`pop()` 可以移除它。
* 每次先丟掉一張，再把下一張移到 queue 最後面。
* 當 queue 只剩一張牌時停止，這張就是最後答案。
* `first` 變數用來處理 discarded cards 的逗號格式。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                           |
| --------------- | ------------------ | -------------------------------------- |
| Logic           | 可能只丟牌，沒有把下一張移到底部。  | 每回合先 discard，再 move 一張到底部。             |
| Edge Cases      | 可能 `n = 1` 時輸出格式錯。 | queue size 大於 1 才進入丟牌流程。               |
| Output Handling | 可能逗號格式錯誤。          | 使用 `first` 控制第一個 discarded card 前不加逗號。 |
| Other           | 可能用 vector 導致操作麻煩。 | 使用 queue 更符合題目操作。                      |

### Reflection

我覺得比較容易錯的是輸出格式，尤其是 discarded cards 中間的逗號。
另外 `n = 1` 時沒有丟掉任何牌，也要能正確輸出。

