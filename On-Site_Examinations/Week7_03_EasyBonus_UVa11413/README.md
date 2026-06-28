# UVa 11413 - Fill the Containers

## 1. Problem Information

Platform: UVa
Problem ID: 11413
Problem Title: Fill the Containers
Problem Link: https://onlinejudge.org/external/114/11413.pdf
Week: 7
Date: 2026/04/07
Theme: Binary search
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/11413.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一排 vessels 的容量，還有 container 的數量 `m`。我要找出最小的 container 容量，讓所有 vessels 可以照原本順序裝進這些 containers 裡。

### What is the input?

* 輸入有多組資料。
* 每組資料先給兩個整數 `n` 和 `m`。

  * `n` 是 vessels 的數量。
  * `m` 是 containers 的數量。
* 接著輸入 `n` 個整數，代表每個 vessel 的容量。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每組資料，輸出最小可行的 container capacity。
* 每組答案輸出一行。

### What are the main rules or constraints?

* vessels 必須照原本順序裝入 containers。
* 不能重新排序 vessels。
* 每個 container 的容量都一樣。
* 要找的是「最小」的可行容量。
* container 容量至少要能裝下最大的單一 vessel。

### What is the core task you must solve?

* 用二分搜尋找出最小容量，並檢查這個容量能不能在 `m` 個 containers 內裝完所有 vessels。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果直接從小容量慢慢試，會很沒效率。
* 這題的答案其實有範圍：最小一定不能小於最大 vessel，最大可以是所有 vessel 總和。
* 所以可以對答案做 binary search。

### Final Strategy

* 先讀入所有 vessels。
* 設定：

  * `low = 最大的 vessel`
  * `high = 所有 vessel 的總和`
* 用 binary search 測試中間值 `mid` 是否可以當作 container 容量。
* 寫一個 `canFill()` 函式：

  * 從第一個 vessel 開始照順序裝。
  * 如果目前 container 還裝得下，就繼續放。
  * 如果裝不下，就換下一個 container。
  * 最後檢查使用的 container 數量是否小於等於 `m`。
* 如果 `mid` 可以裝完，就嘗試更小的容量。
* 如果 `mid` 不行，就把容量調大。
* 最後得到的就是最小可行容量。

What edge cases did you consider?

* 最大的 vessel 一定要能被單一 container 裝下
* vessels 不能重新排序
* `m` 很多時，答案可能就是最大 vessel
* `m` 很少時，答案可能接近總和
* 有多組輸入，要讀到 EOF

## 4. Pseudocode

```text
START
1. While input has n and m:
2.     Read all vessel values.
3.     Set low = maximum vessel value.
4.     Set high = sum of all vessel values.
5.     Set answer = high.
6.     While low <= high:
7.         mid = (low + high) / 2.
8.         If canFill(vessels, m, mid) is true:
9.             answer = mid.
10.            high = mid - 1.
11.        Else:
12.            low = mid + 1.
13.    Print answer.
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
#include <algorithm>

using namespace std;

// A Bonus

bool canFill(vector<int>& vessels, int m, int capacity)
{
    int containerCount = 1;
    int currentSum = 0;

    for (int i = 0; i < vessels.size(); i++)
    {
        if (vessels[i] > capacity)
        {
            return false;
        }

        if (currentSum + vessels[i] <= capacity)
        {
            currentSum += vessels[i];
        }
        else
        {
            containerCount++;
            currentSum = vessels[i];
        }
    }

    return containerCount <= m;
}

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        vector<int> vessels(n);

        int low = 0;
        int high = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> vessels[i];

            low = max(low, vessels[i]);
            high += vessels[i];
        }

        int answer = high;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (canFill(vessels, m, mid))
            {
                answer = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        cout << answer << endl;
    }

    return 0;
}
```

Why it works:

* `low` 設成最大 vessel，確保容量至少能裝下每一個單獨的 vessel。
* `high` 設成全部 vessel 的總和，代表一定可行的最大容量。
* `canFill()` 會照原本順序模擬裝入 containers。
* 如果某個容量可行，就繼續往更小的容量搜尋。
* 如果不可行，就把容量加大。
* 最後留下的 `answer` 就是最小可行 container capacity。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                   |
| --------------- | ----------------- | ------------------------------ |
| Logic           | 可能用線性嘗試容量。        | 用 binary search 搜尋最小可行容量。      |
| Edge Cases      | 可能把 vessels 重新排序。 | 保持原本順序裝入 containers。           |
| Output Handling | 可能找到可行值就直接停。      | 找到可行值後繼續往更小容量找。                |
| Other           | 可能 `low` 設太小。     | `low` 設為最大 vessel，`high` 設為總和。 |

### Reflection

這題讓我學到 binary search 不只可以找陣列裡的數字，也可以拿來找答案。
只要答案有「容量越大越容易成功」這種單調性，就可以用 binary search。

我覺得這題最重要的是 `canFill()` 的判斷。
只要能正確判斷某個容量可不可行，剩下就是用 binary search 找最小值。

