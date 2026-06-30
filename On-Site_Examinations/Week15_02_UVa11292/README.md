# UVa 11292 - Dragon of Loowater

## 1. Problem Information

Platform: UVa
Problem ID: 11292
Problem Title: Dragon of Loowater
Problem Link: https://onlinejudge.org/external/112/11292.pdf
Week: 15
Date: 2026/06/02
Theme: Greedy / Sorting
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11292.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一些 dragon heads 的直徑，還有一些 knights 的身高。
* 如果 knight 的身高大於或等於 dragon head 的直徑，就可以砍掉那個 head。
* 每個 knight 只能用一次，花費等於 knight 的身高。
* 我要用最少總花費砍掉所有 dragon heads。

### What is the input?

* 輸入有多組資料。
* 每組先輸入兩個整數：

  * `n`：dragon heads 的數量
  * `m`：knights 的數量
* 接著輸入 `n` 個整數，代表每個 head 的直徑。
* 再輸入 `m` 個整數，代表每個 knight 的身高。
* 如果 `n = 0` 且 `m = 0`，代表輸入結束。

### What is the expected output?

* 如果可以砍掉所有 heads，輸出最小總花費。
* 如果無法砍掉所有 heads，輸出：

```text 
Loowater is doomed!
```

### What are the main rules or constraints?

* knight 身高必須大於或等於 head 直徑，才能砍掉該 head。
* 每個 knight 只能使用一次。
* 每個 head 都必須被砍掉。
* 目標是讓總花費最小。
* 為了避免浪費，應該用剛好可以砍掉目前 head 的最小 knight。

### What is the core task you must solve?

* 排序 heads 和 knights，然後用 greedy 配對，找出最小花費。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果亂配 knight，可能會用太高的 knight 去砍小 head，導致後面大的 head 沒有人可以砍。
* 所以應該先把 dragon heads 和 knights 都排序。
* 從最小的 head 開始，找第一個可以砍掉它的 knight。
* 這樣可以盡量保留比較高的 knight 給後面的 head。

### Final Strategy

* 每次讀入 `n` 和 `m`。
* 如果 `n == 0 && m == 0`，就結束。
* 把 heads 和 knights 分別存進 vector。
* 對兩個 vector 都排序。
* 使用兩個 index：

  * `headIndex` 指向目前要處理的 head
  * `knightIndex` 指向目前檢查的 knight
* 如果 `knights[knightIndex] >= heads[headIndex]`：

  * 這個 knight 可以砍掉目前 head
  * 把 knight 身高加到 cost
  * `headIndex++`
  * `knightIndex++`
* 如果 knight 太矮：

  * 這個 knight 不能用，直接 `knightIndex++`
* 最後如果 `headIndex == n`，代表所有 heads 都處理完，輸出 cost。
* 否則輸出 `Loowater is doomed!`。

What edge cases did you consider?

* `n = 0` 且 `m = 0` 時要停止
* knights 數量比 heads 少
* 有些 knight 太矮不能砍任何 head
* 剛好所有 heads 都能被砍掉
* 需要用最小可行 knight，避免浪費
* cost 可能較大，所以使用 `long long`

## 4. Pseudocode

```text 
START
1. While input has n and m:
2.     If n == 0 and m == 0:
3.         Stop the program.
4.     Read all dragon heads.
5.     Read all knights.
6.     Sort heads.
7.     Sort knights.
8.     Set headIndex = 0.
9.     Set knightIndex = 0.
10.    Set cost = 0.
11.    While headIndex < n and knightIndex < m:
12.        If knights[knightIndex] >= heads[headIndex]:
13.            cost += knights[knightIndex].
14.            headIndex++.
15.            knightIndex++.
16.        Else:
17.            knightIndex++.
18.    If headIndex == n:
19.        Print cost.
20.    Else:
21.        Print "Loowater is doomed!".
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

* 沒有排序就直接配對
* 用太高的 knight 去砍太小的 head，導致花費變大
* 沒有處理無法砍完所有 heads 的情況
* knight 被重複使用
* 輸出字串格式錯誤

### Correct Code

```cpp 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }

        vector<int> heads(n);
        vector<int> knights(m);

        for (int i = 0; i < n; i++)
        {
            cin >> heads[i];
        }

        for (int i = 0; i < m; i++)
        {
            cin >> knights[i];
        }

        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int headIndex = 0;
        int knightIndex = 0;
        long long cost = 0;

        while (headIndex < n && knightIndex < m)
        {
            if (knights[knightIndex] >= heads[headIndex])
            {
                cost += knights[knightIndex];
                headIndex++;
                knightIndex++;
            }
            else
            {
                knightIndex++;
            }
        }

        if (headIndex == n)
        {
            cout << cost << endl;
        }
        else
        {
            cout << "Loowater is doomed!" << endl;
        }
    }

    return 0;
}
```

Why it works:

* heads 和 knights 都排序後，可以從最小的 head 開始處理。
* 每次選第一個能砍掉目前 head 的 knight，可以避免浪費更高的 knight。
* 如果 knight 太矮，就直接跳過，因為它也不可能砍掉後面更大的 heads。
* 每個 knight 使用後都會讓 `knightIndex++`，所以不會重複使用。
* 如果最後所有 heads 都被處理完，就輸出最小 cost；否則代表 knight 不夠或不夠高。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code           | Correct Code                 |
| --------------- | ------------------- | ---------------------------- |
| Logic           | 可能直接照輸入順序配對。        | 排序後用 greedy 配對。              |
| Edge Cases      | 可能沒處理 knight 不夠的情況。 | 最後檢查 `headIndex == n`。       |
| Output Handling | 可能無解時輸出錯誤。          | 無解時輸出 `Loowater is doomed!`。 |
| Other           | 可能浪費太高的 knight。     | 每次使用最小可行 knight。             |

### Reflection

我覺得重點是不要亂配，而是先排序後從小的 head 開始處理。

每次都找最小但足夠高的 knight，這樣才不會浪費資源。
如果目前 knight 太矮，因為後面的 head 只會更大，所以它也沒有用了，可以直接跳過。


