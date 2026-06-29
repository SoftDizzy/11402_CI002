# UVa 514 - Rails

## 1. Problem Information

Platform: UVa
Problem ID: 514
Problem Title: Rails
Problem Link: https://onlinejudge.org/external/5/514.pdf
Week: 10
Date: 2026/04/28
Theme: Stack
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/514.cpp`

## 2. Problem Statement in My Own Words

* 這題會給火車數量 `n`，火車原本進站順序是 `1, 2, 3, ..., n`。題目會給一個目標出站順序，我要判斷能不能利用一個 station stack 做出這個順序。

### What is the input?

* 輸入有多組資料。
* 每組先輸入一個整數 `n`。
* 如果 `n = 0`，代表整題結束。
* 接著會有很多組目標排列，每組有 `n` 個數字。
* 如果某組目標排列的第一個數字是 `0`，代表這個 `n` 的測資結束。

### What is the expected output?

* 如果可以排出目標順序，輸出：

```text
Yes
```

* 如果不可以排出目標順序，輸出：

```text
No
```

* 每個 `n` 的測資結束後，要輸出一個空行。

### What are the main rules or constraints?

* 火車只能按照 `1` 到 `n` 的順序進入 station。
* station 可以看成一個 stack。
* 最後要判斷能不能得到題目給的出站順序。
* `n = 0` 代表全部輸入結束。
* 目標排列第一個數字是 `0` 代表換下一組 `n`。

### What is the core task you must solve?

* 用 stack 模擬火車進站和出站的過程，判斷目標排列是否可行。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到這題是火車進出站，我想到可以用 stack 模擬。
* 因為 station 裡最後進去的火車會先出來，剛好符合 stack 的後進先出。
* 題目麻煩的地方是輸入格式比較特別，有 `n = 0` 和排列第一個數字為 `0` 兩種結束情況。

### Final Strategy

* 每次先讀入 `n`。
* 如果 `n == 0`，整個程式結束。
* 接著一直讀目標排列。
* 如果目標排列第一個數字是 `0`，輸出空行，結束目前這組 `n`。
* 否則把完整目標排列讀進 `target`。
* 用 `currentTrain` 從 1 開始，模擬火車依序進入 stack。
* 每 push 一台火車進 station，就檢查 stack top 是否等於目前要出的 `target[index]`。
* 如果相同，就一直 pop，並讓 `index` 往下一個目標移動。
* 最後如果 `index == n`，代表整個目標順序都成功完成，輸出 `Yes`，否則輸出 `No`。

What edge cases did you consider?

* `n = 0` 時要結束
* 目標排列第一個數字是 `0` 時要換下一組
* 目標順序本來就是 `1 2 3 ... n`
* 目標順序完全反過來
* stack 為空時不能取 top
* 每組 `n` 結束後要空一行

## 4. Pseudocode

```text
START
1. While input has n:
2.     If n == 0:
3.         Stop the program.
4.     Repeat:
5.         Read the first number of target.
6.         If the first number is 0:
7.             Print a blank line.
8.             Stop reading targets for this n.
9.         Read the remaining n - 1 numbers into target.
10.        Create an empty stack station.
11.        Set currentTrain = 1.
12.        Set index = 0.
13.        While currentTrain <= n:
14.            Push currentTrain into station.
15.            Increase currentTrain.
16.            While station is not empty and station.top equals target[index]:
17.                Pop station.
18.                Increase index.
19.        If index == n:
20.            Print Yes.
21.        Else:
22.            Print No.
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
#include <stack>

using namespace std;

// B

int main()
{
    int n;

    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        while (true)
        {
            vector<int> target(n);

            cin >> target[0];

            if (target[0] == 0)
            {
                cout << endl;
                break;
            }

            for (int i = 1; i < n; i++)
            {
                cin >> target[i];
            }

            stack<int> station;
            int currentTrain = 1;
            int index = 0;

            while (currentTrain <= n)
            {
                station.push(currentTrain);
                currentTrain++;

                while (!station.empty() && station.top() == target[index])
                {
                    station.pop();
                    index++;
                }
            }

            if (index == n)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}
```

Why it works:

* 程式先處理 `n = 0` 的整體結束條件。
* 對每個 `n`，會持續讀取多組目標排列。
* 如果目標排列第一個數字是 `0`，代表目前這組 `n` 結束，並輸出空行。
* 模擬時，火車依照 `1` 到 `n` 的順序進入 stack。
* 每次 stack top 剛好等於目前需要的目標車廂，就 pop 出來。
* 如果最後 `index == n`，代表目標排列全部成功完成，所以輸出 `Yes`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                      |
| --------------- | ------------------ | --------------------------------- |
| Logic           | 可能只直接比較原始順序和目標順序。  | 使用 stack 模擬 station 的進出順序。        |
| Edge Cases      | 可能沒處理 `0` 結束條件。    | 同時處理 `n = 0` 和 target 第一個數字為 `0`。 |
| Output Handling | 可能少印每組之間的空行。       | target 第一個數字是 `0` 時印空行。           |
| Other           | 可能沒有持續 pop 可出站的火車。 | 每次 push 後用 while 持續檢查可不可以 pop。    |

### Reflection

這題是 stack 模擬題。
我覺得最容易錯的不是 stack 本身，而是輸入格式，因為有兩種不同的 `0` 要判斷。

這題讓我更理解 stack 的用途。
當題目有「最後進去的東西可能最先出來」這種情況時，就很適合用 stack。

