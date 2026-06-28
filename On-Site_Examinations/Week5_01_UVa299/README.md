# UVa 299 - Train Swapping

## 1. Problem Information

Platform: UVa
Problem ID: 299
Problem Title: Train Swapping
Problem Link: https://onlinejudge.org/external/2/299.pdf
Week: 5
Date: 2026/03/24
Theme: Sorting basics
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/42_299.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一列火車車廂的順序，要把車廂排成由小到大的順序，並計算最少需要交換幾次相鄰車廂。

### What is the input?

* 第一行是一個整數，代表有幾組測資。
* 每組測資先輸入一個整數 `n`，代表有幾個車廂。
* 接著輸入 `n` 個整數，代表目前車廂的排列順序。

### What is the expected output?

* 每組測資要輸出：

```text
Optimal train swapping takes x swaps.
```

其中 `x` 是需要交換的次數。

### What are the main rules or constraints?

* 只能交換相鄰的兩個車廂。
* 目標是把車廂排成遞增順序。
* 每交換一次就要計數一次。
* 輸出格式要完全符合題目要求。

### What is the core task you must solve?

* 計算用相鄰交換把陣列排好序時，需要交換幾次。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想到這題可以用 Bubble Sort。
* 因為 Bubble Sort 本來就是一直比較相鄰兩個元素，如果順序錯就交換。
* 題目剛好也是要計算相鄰車廂交換次數，所以每次 swap 就可以直接加 1。

### Final Strategy

* 先讀入測資數量。
* 每組測資讀入車廂數量 `n`。
* 用 `vector<int>` 存車廂順序。
* 用雙層迴圈做 Bubble Sort。
* 如果 `v[i] > v[i + 1]`，就交換兩個數字，並讓 `count++`。
* 最後輸出交換次數。

What edge cases did you consider?

* 車廂本來就已經排序好，交換次數是 0
* 車廂順序完全反過來，交換次數會比較多
* 只有一個車廂時，不需要交換
* 有多組測資
* 輸出句子的格式不能打錯

## 4. Pseudocode

```text
START
1. Read testbase.
2. Repeat for each test case:
3.     Read n.
4.     Read n train numbers into vector v.
5.     Set count = 0.
6.     For pass from 0 to n - 2:
7.         For i from 0 to n - 2:
8.             If v[i] > v[i + 1]:
9.                 Swap v[i] and v[i + 1].
10.                Add 1 to count.
11.    Print the answer sentence with count.
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

//      A

int main()
{
    int testbase;
    cin >> testbase;

    while (testbase--)
    {
        int n;
        cin >> n;

        vector<int> v(n);

        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        int count = 0;
                                                            // Bubble Sort 就是雙層迴圈，反覆比較相鄰兩個元素，順序錯就交換。
        for (int pass = 0; pass < n - 1; pass++)            // 遇到bubble sort 可以用雙層迴圈搞定   最多只要多做 n - 1 輪 就可以完成
        {
            for (int i = 0; i < n - 1; i++)
            {
                if (v[i] > v[i + 1])
                {
                    int temp = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = temp;

                    count++;
                }
            }
        }

        cout << "Optimal train swapping takes " << count << " swaps." << endl;
    }

    return 0;
}
```

Why it works:

* 這份程式用 Bubble Sort 模擬相鄰車廂交換。
* 每次發現相鄰兩個車廂順序錯誤，就交換它們。
* 每交換一次就把 `count` 加 1，所以最後的 `count` 就是需要的交換次數。
* 程式可以處理多組測資，輸出格式也符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                | Correct Code                               |
| --------------- | ------------------------ | ------------------------------------------ |
| Logic           | 可能只把車廂排序，沒有模擬相鄰交換。       | 使用 Bubble Sort，符合相鄰交換的規則。                  |
| Edge Cases      | 可能沒處理已排序或單一車廂。           | 已排序時不會交換，count 會保持 0。                      |
| Output Handling | 可能輸出格式和題目不一樣。            | 輸出 `Optimal train swapping takes x swaps.` |
| Other           | 可能用 `sort()`，但無法直接算交換次數。 | 每次手動交換時都累加 `count`。                        |

### Reflection
下次看到「相鄰交換」這種題目時，可以先想到 Bubble Sort 或 inversion count。

