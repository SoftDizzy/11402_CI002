# UVa 10821 - Constructing BST

## 1. Problem Information

Platform: UVa
Problem ID: 10821
Problem Title: Constructing BST
Problem Link: https://onlinejudge.org/external/108/10821.pdf
Week: 12
Date: 2026/05/12
Theme: Binary Search Tree
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10821.cpp`

## 2. Problem Statement in My Own Words

* 這題會給兩個數字 `N` 和 `H`。我要用 `1` 到 `N` 這些數字建立一棵 BST，並且讓這棵 BST 的高度是 `H`。如果可以建立，就輸出其中一種合法 BST 的 preorder；如果不行，就輸出 Impossible。

### What is the input?

* 輸入有多組資料。
* 每組資料有兩個整數：

  * `N`：節點數量
  * `H`：要求的高度
* 要一直讀到 EOF。

### What is the expected output?

* 每組資料要輸出：

```text 
Case x:
```

* 如果無法建立符合條件的 BST，輸出：

```text 
Case x: Impossible.
```

* 如果可以建立，就在後面輸出 preorder traversal。

### What are the main rules or constraints?

* BST 使用的值是 `1` 到 `N`。
* BST 的 inorder 會是遞增順序。
* 要建立高度剛好為 `H` 的 BST。
* 如果高度太大或太小，都可能無法建立。
* 輸出的是 preorder，也就是：

```text 
root -> left subtree -> right subtree
```

### What is the core task you must solve?

* 判斷是否能用 `N` 個節點建立高度 `H` 的 BST，如果可以，就構造一種合法 preorder。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* BST 的 inorder 一定會是排序好的，所以如果使用 `1` 到 `N`，只要決定 root，左邊的值就會在 left subtree，右邊的值就會在 right subtree。
* 這題不是單純建立普通 BST，而是要控制高度。
* 所以要先判斷 `N` 和 `H` 是否合理，再用遞迴去安排 root 和左右子樹。

### Final Strategy

* 先判斷是否不可能：

  * 如果 `H > N`，代表高度比節點數還多，不可能。
  * 如果 `N > 2^H - 1`，代表高度 `H` 最多容納的節點數不夠，也不可能。
* `maxNodes(height)` 用來計算高度 `height` 最多可以有幾個節點。
* `minHeight(nodes)` 用來找某個節點數至少需要多少高度。
* `buildBST(startValue, nodes, height, answer)` 用來建立目前子樹的 preorder。
* 為了讓整棵樹高度達到 `height`，右子樹保留 `height - 1` 的高度。
* 左子樹放入能放的多餘節點數。
* root 的值就是：

```text 
startValue + leftNodes
```

* 因為左子樹有 `leftNodes` 個節點，所以 root 前面的值都會在左子樹。
* 每次先把 root 放進答案，再遞迴處理 left subtree 和 right subtree，就會得到 preorder。

What edge cases did you consider?

* `H > N` 時不可能
* `N > 2^H - 1` 時不可能
* `N = 1` 的情況
* 左子樹節點數可能是 0
* 右子樹節點數可能是 0
* `2^H` 可能很大，所以用 `long long` 和 LIMIT 避免溢位
* 輸入有多組，要讀到 EOF

## 4. Pseudocode

Write the main steps of your solution before showing the actual code.

```text 
START
1. Set cases = 1.
2. While input has N and H:
3.     Print "Case cases:".
4.     If H > N or maxNodes(H) < N:
5.         Print " Impossible."
6.     Else:
7.         Create answer vector.
8.         Call buildBST(1, N, H, answer).
9.         Print all numbers in answer.
10.    Increase cases by 1.

Function maxNodes(height):
1. If height <= 0:
2.     Return 0.
3. Calculate 2^height - 1.
4. If value is too large, return LIMIT.
5. Return value.

Function minHeight(nodes):
1. Set height = 0.
2. While maxNodes(height) < nodes:
3.     height++.
4. Return height.

Function buildBST(startValue, nodes, height, answer):
1. If nodes <= 0:
2.     Return.
3. maxLeftNodes = maxNodes(height - 1).
4. leftNodes = min(nodes - height, maxLeftNodes).
5. rightNodes = nodes - 1 - leftNodes.
6. root = startValue + leftNodes.
7. Push root into answer.
8. leftHeight = minHeight(leftNodes).
9. Build left subtree with startValue, leftNodes, leftHeight.
10. Build right subtree with root + 1, rightNodes, height - 1.
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

// B Bonus

const long long LIMIT = 1000000000000000000LL;

long long maxNodes(int height)
{
    if (height <= 0)
    {
        return 0;
    }

    long long nodes = 1;

    for (int i = 0; i < height; i++)
    {
        nodes *= 2;

        if (nodes > LIMIT)
        {
            return LIMIT;
        }
    }

    return nodes - 1;
}

int minHeight(int nodes)
{
    int height = 0;

    while (maxNodes(height) < nodes)
    {
        height++;
    }

    return height;
}

void buildBST(int startValue, int nodes, int height, vector<int> &answer)
{
    if (nodes <= 0)
    {
        return;
    }

    long long maxLeftNodes = maxNodes(height - 1);

    int leftNodes = min((long long)(nodes - height), maxLeftNodes);
    int rightNodes = nodes - 1 - leftNodes;

    int root = startValue + leftNodes;

    answer.push_back(root);

    int leftHeight = minHeight(leftNodes);

    buildBST(startValue, leftNodes, leftHeight, answer);
    buildBST(root + 1, rightNodes, height - 1, answer);
}

int main()
{
    int N, H;
    int cases = 1;

    while (cin >> N >> H)
    {
        cout << "Case " << cases << ":";

        if (H > N || maxNodes(H) < N)
        {
            cout << " Impossible." << endl;
        }
        else
        {
            vector<int> answer;

            buildBST(1, N, H, answer);

            for (int i = 0; i < answer.size(); i++)
            {
                cout << " " << answer[i];
            }

            cout << endl;
        }

        cases++;
    }

    return 0;
}
```

Why it works:

* 程式先用節點數和高度限制判斷是否 Impossible。
* `maxNodes(H)` 可以知道高度 `H` 最多能放多少節點。
* BST 使用 `1` 到 `N`，所以 root 左邊的值一定屬於左子樹，右邊的值一定屬於右子樹。
* `buildBST()` 透過分配左子樹節點數，決定目前 root。
* 先輸出 root，再建立左子樹與右子樹，所以輸出順序是 preorder。
* 使用 `long long` 和 `LIMIT` 可以避免計算節點上限時溢位。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code                    | Correct Code                       |
| --------------- | ---------------------------- | ---------------------------------- |
| Logic           | 可能只會建立普通 BST。                | 會根據 `N` 和 `H` 控制樹的高度。              |
| Edge Cases      | 可能沒有判斷 Impossible。           | 先檢查 `H > N` 和 `maxNodes(H) < N`。   |
| Output Handling | 可能輸出 inorder 或 postorder。    | 按照 preorder 輸出 root、left、right。    |
| Other           | 可能 `2^H` 溢位。                 | 使用 按照 preorder 輸出 root、left、right。 |
| Other           | 可能 ` `long long` 和 LIMIT 保護。 |                                    |

### Reflection

它不是只有走訪樹，而是要自己構造一棵符合高度的 BST。
我覺得最重要的是先判斷不可能的情況，不然後面建樹會很容易出錯。

這題也讓我更理解 BST 的 inorder 性質。
只要使用 `1` 到 `N`，root 左邊的數字就會自然形成左子樹，root 右邊的數字就會形成右子樹。

