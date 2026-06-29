# UVa 11615 - Family Tree

## 1. Problem Information

Platform: UVa
Problem ID: 11615
Problem Title: Family Tree
Problem Link: https://onlinejudge.org/external/116/11615.pdf
Week: 12
Date: 2026/05/12
Theme: Complete Binary Tree Indexing
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11615.cpp`

## 2. Problem Statement in My Own Words

* 這題是在算家族樹的人數。完整的第 `N` 代 family tree 原本會有 `2^N - 1` 個人，但因為題目給的兩個人 `A` 和 `B` 有共同的祖先，所以有些人會重複計算。我要算出扣掉重複後，實際不同的人數。

### What is the input?

* 第一行是一個整數 `T`，代表有幾組測資。
* 每組測資有三個整數：

  * `N`
  * `A`
  * `B`

### What is the expected output?

* 每組測資輸出一個整數。
* 代表扣掉重複祖先後，實際不同的人數。

### What are the main rules or constraints?

* 完整 `N` 代家族樹人數是 `2^N - 1`。
* 題目中的人可以用 complete binary tree 的編號方式理解。
* 編號越往下，generation 越深。
* 對某個編號 `x`，一直除以 2，可以往父節點走。
* `A` 和 `B` 造成某些祖先重複，所以要扣掉重複的部分。

### What is the core task you must solve?

* 先算出完整家族樹的人數，再找出重複祖先對應的層數，最後扣掉重複人數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始看到 family tree，可以想到它像 complete binary tree。
* 如果一棵完整二元樹有 `N` 層，那節點數是 `2^N - 1`。
* 題目重點不是建立整棵樹，而是用編號和 generation 去算重複的人數。
* 所以應該用數學計算，不需要真的建樹。

### Final Strategy

* 寫一個 `getGeneration(x)` 函式。
* 對 `x` 不斷除以 2，計算它位於第幾個 generation。
* 分別算出 `A` 和 `B` 的 generation。
* 取比較深的那個 generation。
* 完整人數為：

```text 
2^N - 1
```

* 重複層數為：

```text 
N - deeperGeneration
```

* 如果重複層數大於 0，就代表有需要扣掉的重複 ancestors。
* 重複人數為：

```text 
2 * (2^duplicateLevel - 1)
```

* 最後答案就是：

```text 
totalPeople - duplicatePeople
```

What edge cases did you consider?

* `A` 和 `B` 位在不同 generation
* `A` 或 `B` 已經在很深的位置
* `duplicateLevel` 小於或等於 0 時，不能再扣人數
* `2^N` 可能比較大，所以用 `long long`
* 不需要真的建立 binary tree

## 4. Pseudocode

```text 
START
1. Read T.
2. Repeat T times:
3.     Read N, A, B.
4.     generationA = getGeneration(A).
5.     generationB = getGeneration(B).
6.     deeperGeneration = max(generationA, generationB).
7.     totalPeople = 2^N - 1.
8.     duplicateLevel = N - deeperGeneration.
9.     duplicatePeople = 0.
10.    If duplicateLevel > 0:
11.        duplicatePeople = 2 * (2^duplicateLevel - 1).
12.    Print totalPeople - duplicatePeople.

Function getGeneration(x):
1. Set generation = 0.
2. While x > 0:
3.     generation++.
4.     x = x / 2.
5. Return generation.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp 
No failed version was saved.
```

### Correct Code

```cpp id="4b00jy"
#include <iostream>
#include <algorithm>

using namespace std;

// A

int getGeneration(int x)
{
    int generation = 0;

    while (x > 0)
    {
        generation++;
        x /= 2;
    }

    return generation;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, A, B;
        cin >> N >> A >> B;

        int generationA = getGeneration(A);
        int generationB = getGeneration(B);

        int deeperGeneration = max(generationA, generationB);

        long long totalPeople = (1LL << N) - 1;

        int duplicateLevel = N - deeperGeneration;

        long long duplicatePeople = 0;

        if (duplicateLevel > 0)
        {
            duplicatePeople = 2 * ((1LL << duplicateLevel) - 1);
        }

        cout << totalPeople - duplicatePeople << endl;
    }

    return 0;
}
```

Why it works:

* `getGeneration()` 可以透過不斷除以 2，算出節點在 complete binary tree 中的 generation。
* `totalPeople = 2^N - 1` 可以直接算出完整家族樹的人數。
* 透過較深的 generation，可以知道剩下會重複的祖先層數。
* 重複的部分有兩邊，所以用 `2 * (2^duplicateLevel - 1)` 扣掉。
* 最後輸出完整人數減掉重複人數，就是實際不同的人數。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code            | Correct Code                      |
| --------------- | -------------------- | --------------------------------- |
| Logic           | 可能想建立整棵 family tree。 | 用 complete binary tree 的編號規律直接計算。 |
| Edge Cases      | 可能 generation 算錯。    | 用除以 2 的方式找 generation。            |
| Output Handling | 可能數字型別不夠大。           | 使用 `long long` 計算人數。              |
| Other           | 可能重複祖先扣錯。            | 根據 `duplicateLevel` 計算重複人數。       |

### Reflection

我學到 complete binary tree 的編號很重要。
一個節點除以 2 就可以找到父節點，而一直除以 2 就可以知道它大概在哪一層。

這題也提醒我，遇到樹的題目不一定要真的建樹。
有時候只要利用編號規律和公式，就可以更快解決。
