# UVa 679 - Dropping Balls

## 1. Problem Information

Platform: UVa
Problem ID: 679
Problem Title: Dropping Balls
Problem Link: https://onlinejudge.org/external/6/679.pdf
Week: 12
Date: 2026/05/12
Theme: Complete Binary Tree Indexing
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/679.cpp`

## 2. Problem Statement in My Own Words

* 這題是在一棵完整 binary tree 中丟球。每個節點都有開關，球經過時會根據開關狀態往左或往右走，並且開關會改變方向。題目要問第 `I` 顆球最後會掉到哪一個 leaf node。

### What is the input?

* 第一行是一個整數 `testCase`，代表有幾組測資。
* 每組測資有兩個整數：

  * `D`：樹的深度
  * `I`：第幾顆球

### What is the expected output?

* 每組測資輸出一個整數。
* 代表第 `I` 顆球最後停下來的 leaf node 編號。

### What are the main rules or constraints?

* 樹是 complete binary tree。
* root 編號是 `1`。
* 對於編號 `node`：

  * left child 是 `node * 2`
  * right child 是 `node * 2 + 1`
* 不需要真的模擬前面所有球。
* 可以直接根據第 `I` 顆球的奇偶判斷往左或往右。

### What is the core task you must solve?

* 利用 complete binary tree 的編號規則，直接算出第 `I` 顆球的路徑和最後節點。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果真的模擬每一顆球和每個開關，會很麻煩，也可能太慢。
* 題目其實只問第 `I` 顆球最後的位置，所以可以直接推它每一層走哪邊。
* 在每個節點，第奇數顆到這裡的球會往左，第偶數顆到這裡的球會往右。

### Final Strategy

* 每組測資讀入 `D` 和 `I`。
* 從 root node `1` 開始。
* 因為最後要走到第 `D` 層，所以迴圈跑 `D - 1` 次。
* 每一層判斷 `I`：

  * 如果 `I` 是奇數，往左走，`node = node * 2`。
  * 如果 `I` 是偶數，往右走，`node = node * 2 + 1`。
* 走完之後，要更新 `I`：

  * 往左時，新的 `I = (I + 1) / 2`
  * 往右時，新的 `I = I / 2`
* 最後輸出 `node`。

What edge cases did you consider?

* `D = 1` 時，球會停在 root
* `I` 是奇數時往左
* `I` 是偶數時往右
* 不需要建立整棵 binary tree
* 節點編號用公式計算即可
* 多組測資要逐一處理

## 4. Pseudocode

```text
START
1. Read testCase.
2. Repeat testCase times:
3.     Read D and I.
4.     Set node = 1.
5.     For level from 1 to D - 1:
6.         If I is odd:
7.             node = node * 2.
8.             I = (I + 1) / 2.
9.         Else:
10.            node = node * 2 + 1.
11.            I = I / 2.
12.    Print node.
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

* 真的模擬前面所有球，導致效率太差
* 沒有理解 complete binary tree 的節點編號
* 往左或往右後，忘記更新 `I`
* 迴圈層數跑錯，導致停在錯誤節點
* 把 left child 和 right child 的公式寫錯

### Correct Code

```cpp 
#include <iostream>

using namespace std;

// B

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int D, I;
        cin >> D >> I;

        int node = 1;

        for (int level = 1; level < D; level++)
        {
            if (I % 2 == 1)
            {
                node = node * 2;
                I = (I + 1) / 2;
            }
            else
            {
                node = node * 2 + 1;
                I = I / 2;
            }
        }

        cout << node << endl;
    }

    return 0;
}
```

Why it works:

* 程式不需要建立樹，只用節點編號公式往下走。
* 當 `I` 是奇數時，代表這顆球在目前節點會往左。
* 當 `I` 是偶數時，代表這顆球在目前節點會往右。
* 每走到下一層後，會把 `I` 更新成在下一個子樹中的相對球數。
* 走 `D - 1` 次後，就會到達 leaf node，輸出的 `node` 就是答案。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code     | Correct Code           |
| --------------- | ------------- | ---------------------- |
| Logic           | 可能真的模擬所有球和開關。 | 直接根據 `I` 的奇偶推算路徑。      |
| Edge Cases      | 可能層數跑錯。       | 迴圈從第 1 層跑到第 `D - 1` 層。 |
| Output Handling | 可能輸出中間節點。     | 最後才輸出 leaf node。       |
| Other           | 可能需要建立完整樹。    | 只用節點編號公式，不建樹。          |

### Reflection

可以用 complete binary tree 的規律直接算。
如果真的一顆一顆球模擬，會比較慢，也比較容易寫錯。

我學到遇到 binary tree 編號題時，可以先觀察左右子節點的公式。
這題只要知道 `I` 的奇偶，就可以決定每一層要往左還是往右。

