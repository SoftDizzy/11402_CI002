# UVa 12347 - Binary Search Tree

## 1. Problem Information

Platform: UVa
Problem ID: 12347
Problem Title: Binary Search Tree
Problem Link: https://onlinejudge.org/external/123/12347.pdf
Week: 12
Date: 2026/05/12
Theme: Binary Search Tree
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12347.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一棵 BST 的 preorder traversal，我要輸出這棵樹的 postorder traversal。

### What is the input?

* 輸入是一串整數。
* 這些整數代表 BST 的 preorder traversal。
* 要一直讀到 EOF。

### What is the expected output?

* 輸出這棵 BST 的 postorder traversal。
* 每個節點值輸出一行。

### What are the main rules or constraints?

* BST 的左子樹節點值都小於 root。
* BST 的右子樹節點值都大於 root。
* Preorder 順序是：

```text 
root -> left subtree -> right subtree
```

* Postorder 順序是：

```text 
left subtree -> right subtree -> root
```

### What is the core task you must solve?

* 根據 BST 的性質，從 preorder 直接推回 postorder。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以想到先把 BST 建出來，再用 postorder 輸出。
* 但是其實不用真的建樹。
* 因為 preorder 第一個合法的數字就是目前子樹的 root。
* 再利用 BST 的大小範圍，就可以判斷這個節點是不是屬於目前子樹。

### Final Strategy

* 先把所有輸入存到 `preorder` 裡。
* 用 `indexNow` 表示目前 preorder 讀到哪一個位置。
* 寫一個遞迴函式 `printPostorder(low, high)`。
* 如果目前值不在 `(low, high)` 範圍內，代表它不屬於這棵子樹，直接 return。
* 如果目前值合法，就把它當作 root，並讓 `indexNow++`。
* 接著遞迴處理左子樹，合法範圍是 `(low, root)`。
* 再遞迴處理右子樹，合法範圍是 `(root, high)`。
* 最後輸出 root，這樣就符合 postorder。

What edge cases did you consider?

* 輸入要讀到 EOF
* 可能只有一個節點
* 左子樹或右子樹可能不存在
* 節點值要符合 BST 範圍
* 不需要真的建立 tree node
* 使用 `long long` 範圍避免邊界值問題

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text 
START
1. Read all integers into preorder.
2. Set indexNow = 0.
3. Call printPostorder(-infinity, +infinity).

Function printPostorder(low, high):
1. If indexNow is out of range:
2.     Return.
3. Set root = preorder[indexNow].
4. If root is not inside (low, high):
5.     Return.
6. Increase indexNow.
7. Call printPostorder(low, root) for left subtree.
8. Call printPostorder(root, high) for right subtree.
9. Print root.
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
#include <climits>

using namespace std;

// A Bonus

vector<int> preorder;
int indexNow = 0;

void printPostorder(long long low, long long high)
{
    if (indexNow >= preorder.size())
    {
        return;
    }

    int root = preorder[indexNow];

    if (root <= low || root >= high)
    {
        return;
    }

    indexNow++;

    printPostorder(low, root);
    printPostorder(root, high);

    cout << root << endl;
}

int main()
{
    int x;

    while (cin >> x)
    {
        preorder.push_back(x);
    }

    printPostorder(LLONG_MIN, LLONG_MAX);

    return 0;
}
```

Why it works:

* `preorder[indexNow]` 代表目前可能的 root。
* 用 `(low, high)` 限制目前子樹能接受的節點值。
* 如果目前值不在範圍內，就代表它屬於其他子樹，不應該在這裡處理。
* 左子樹的範圍是小於 root，右子樹的範圍是大於 root。
* 先遞迴左子樹，再遞迴右子樹，最後輸出 root，所以輸出順序就是 postorder。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code            | Correct Code             |
| --------------- | -------------------- | ------------------------ |
| Logic           | 可能先建樹再 traversal。    | 直接用 preorder 和 BST 範圍遞迴。 |
| Edge Cases      | 可能左右子樹邊界判斷錯。         | 用 `(low, high)` 控制合法範圍。  |
| Output Handling | 可能 root 輸出時機錯。       | 左右子樹處理完後才輸出 root。        |
| Other           | 可能需要額外 tree node 結構。 | 不建樹，直接輸出 postorder。      |

### Reflection

這題讓我更理解 BST 的 preorder 和 postorder 差別。
Preorder 是先看到 root，而 postorder 是最後才輸出 root。

我覺得這題重要的地方是範圍限制。
只要知道目前子樹允許的值範圍，就可以判斷 preorder 裡的下一個數字是不是屬於這棵子樹。

