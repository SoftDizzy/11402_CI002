# UVa 12356 - Army Buddies

## 1. Problem Information

Platform: UVa
Problem ID: 12356
Problem Title: Army Buddies
Problem Link: https://onlinejudge.org/external/123/12356.pdf
Week: 15
Date: 2026/06/02
Theme: Linked List / Array Simulation
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/12356.cpp`

## 2. Problem Statement in My Own Words

* 這題有一排士兵，編號從 `1` 到 `S`。
* 每次會有一段連續的士兵 `L` 到 `R` 被移除。
* 移除後，要輸出這段士兵左邊最近還活著的人，以及右邊最近還活著的人。
* 如果某一邊沒有人，就輸出 `*`。

### What is the input?

* 輸入有多組資料。
* 每組先輸入兩個整數：

  * `S`：士兵數量
  * `B`：有幾次移除事件
* 接著有 `B` 行，每行有兩個整數 `L` 和 `R`。
* 如果 `S = 0` 且 `B = 0`，代表輸入結束。

### What is the expected output?

* 每次移除後，要輸出左右兩邊最近還活著的士兵。
* 如果左邊沒有士兵，左邊輸出 `*`。
* 如果右邊沒有士兵，右邊輸出 `*`。
* 每組資料結束後輸出：

```text 
-
```

### What are the main rules or constraints?

* 每次移除的是一段連續區間 `L ~ R`。
* 要快速找到移除區間左邊和右邊還活著的士兵。
* 不能每次都慢慢往左或往右找，可能會太慢。
* 可以用陣列模擬 linked list，記錄每個士兵目前左右鄰居。

### What is the core task you must solve?

* 核心任務是用 `left` 和 `right` 陣列維護目前還活著士兵的連結關係，快速刪除一段區間並輸出左右 buddy。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可能會想用陣列標記哪些士兵被移除，然後每次從 `L` 往左找、從 `R` 往右找。
* 但如果資料很多，這樣每次線性搜尋會太慢。
* 所以比較好的方法是把士兵看成一條 linked list。
* 只要知道一段區間左邊是誰、右邊是誰，就可以把這段區間直接跳過。

### Final Strategy

* 對每組資料建立兩個陣列：

  * `left[i]` 表示 `i` 左邊最近還活著的士兵。
  * `right[i]` 表示 `i` 右邊最近還活著的士兵。
* 初始化時：

  * `left[i] = i - 1`
  * `right[i] = i + 1`
* 對最後一個士兵，`right[S] = 0`，代表右邊沒有人。
* 每次讀入要移除的區間 `L R`。
* 先找：

  * `leftBuddy = left[L]`
  * `rightBuddy = right[R]`
* 輸出 `leftBuddy` 和 `rightBuddy`。
* 如果 buddy 是 `0`，就輸出 `*`。
* 接著把左右兩邊重新連起來：

  * 如果 `leftBuddy != 0`，令 `right[leftBuddy] = rightBuddy`
  * 如果 `rightBuddy != 0`，令 `left[rightBuddy] = leftBuddy`

What edge cases did you consider?

* 移除區間包含第一個士兵
* 移除區間包含最後一個士兵
* 左邊沒有 buddy 要輸出 `*`
* 右邊沒有 buddy 要輸出 `*`
* 一次移除整段剩下的人
* 每組資料結束後要輸出 `-`
* `S = 0` 且 `B = 0` 時要停止

## 4. Pseudocode

```text 
START
1. While input has S and B:
2.     If S == 0 and B == 0:
3.         Stop the program.
4.     Create left and right arrays.
5.     For i from 1 to S:
6.         left[i] = i - 1.
7.         right[i] = i + 1.
8.     Set right[S] = 0.
9.     Repeat B times:
10.        Read L and R.
11.        leftBuddy = left[L].
12.        rightBuddy = right[R].
13.        If leftBuddy == 0:
14.            Print "*".
15.        Else:
16.            Print leftBuddy.
17.        Print space.
18.        If rightBuddy == 0:
19.            Print "*".
20.        Else:
21.            Print rightBuddy.
22.        Print newline.
23.        If leftBuddy != 0:
24.            right[leftBuddy] = rightBuddy.
25.        If rightBuddy != 0:
26.            left[rightBuddy] = leftBuddy.
27.    Print "-".
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

// A Bonus

int main()
{
    int S, B;

    while (cin >> S >> B)
    {
        if (S == 0 && B == 0)
        {
            break;
        }

        vector<int> left(S + 2);
        vector<int> right(S + 2);

        for (int i = 1; i <= S; i++)
        {
            left[i] = i - 1;
            right[i] = i + 1;
        }

        right[S] = 0;

        for (int i = 0; i < B; i++)
        {
            int L, R;
            cin >> L >> R;

            int leftBuddy = left[L];
            int rightBuddy = right[R];

            if (leftBuddy == 0)
            {
                cout << "*";
            }
            else
            {
                cout << leftBuddy;
            }

            cout << " ";

            if (rightBuddy == 0)
            {
                cout << "*";
            }
            else
            {
                cout << rightBuddy;
            }

            cout << endl;

            if (leftBuddy != 0)
            {
                right[leftBuddy] = rightBuddy;
            }

            if (rightBuddy != 0)
            {
                left[rightBuddy] = leftBuddy;
            }
        }

        cout << "-" << endl;
    }

    return 0;
}
```

Why it works:

* `left[i]` 和 `right[i]` 可以記錄目前士兵 `i` 左右最近還活著的人。
* 移除 `L ~ R` 時，`left[L]` 就是左邊最近還活著的 buddy，`right[R]` 就是右邊最近還活著的 buddy。
* 輸出後，把 `leftBuddy` 和 `rightBuddy` 重新連接起來，就等於把中間被移除的區間跳過。
* 如果 buddy 是 `0`，代表那一邊沒有活著的士兵，所以輸出 `*`。
* 這樣每次移除只需要常數時間，不用從左右慢慢搜尋。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code                         |
| --------------- | ------------------ | ------------------------------------ |
| Logic           | 可能每次從左右線性搜尋 buddy。 | 使用陣列模擬 linked list。                  |
| Edge Cases      | 可能左右邊界輸出錯。         | 用 `0` 表示沒有 buddy，輸出 `*`。             |
| Output Handling | 可能忘記每組最後的 `-`。     | 每組資料處理完後輸出 `-`。                      |
| Other           | 可能移除後沒有更新鄰居。       | 會把 `leftBuddy` 和 `rightBuddy` 重新接起來。 |

### Reflection

這題讓我學到可以用陣列模擬 linked list。
如果真的每次都往左右找還活著的人，資料大時會很慢。

用 `left` 和 `right` 陣列後，刪除一段區間就只需要更新兩個位置。
這種方法很適合處理「連續刪除」或「快速找左右鄰居」的題目。

