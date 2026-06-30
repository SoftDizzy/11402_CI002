# UVa 10020 - Minimal coverage

## 1. Problem Information

Platform: UVa
Problem ID: 10020
Problem Title: Minimal coverage
Problem Link: https://onlinejudge.org/external/100/10020.pdf
Week: 15
Date: 2026/06/02
Theme: Greedy / Interval Coverage
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/10020.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個目標區間 `[0, M]`，還有很多條線段。
* 我要從這些線段中選出最少的線段，讓它們可以完整覆蓋 `[0, M]`。
* 如果沒辦法完整覆蓋，就輸出 `0`。

### What is the input?

* 第一行是一個整數 `testCase`，代表有幾組測資。
* 每組測資先輸入一個整數 `M`。
* 接著會輸入很多條線段，每條線段有兩個整數 `L` 和 `R`。
* 當輸入 `0 0` 時，代表目前這組測資的線段輸入結束。

### What is the expected output?

* 如果無法完整覆蓋 `[0, M]`，輸出：

```text 
0
```

* 如果可以覆蓋，先輸出需要的線段數量。
* 接著輸出選到的每一條線段。
* 不同測資之間要輸出空行。

### What are the main rules or constraints?

* 目標是覆蓋 `[0, M]`。
* 線段可以超出 `[0, M]` 的範圍。
* 要選最少數量的線段。
* 如果中間有缺口，就無法完整覆蓋。
* 每一步應該選可以接上目前覆蓋範圍，而且右端點延伸最遠的線段。

### What is the core task you must solve?

* 是使用 greedy 方法，每次選出能把目前覆蓋範圍往右推最遠的線段。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始如果暴力嘗試所有線段組合，會太複雜。
* 這題是典型的 interval coverage。
* 因為要用最少線段覆蓋一段連續區間，所以可以從左到右貪心選。
* 目前假設已經覆蓋到 `current`，下一條線段一定要滿足左端點 `L <= current`，不然中間就會有空缺。

### Final Strategy

* 先讀入所有線段，直到遇到 `0 0`。
* 將所有線段依照左端點排序。
* 設定 `current = 0`，代表目前已經覆蓋到的位置。
* 每一輪找出所有 `L <= current` 的線段。
* 在這些線段中，選右端點 `R` 最大的那條。
* 如果找不到可以延伸的線段，代表無法覆蓋，設定 `possible = false`。
* 如果找得到，就把該線段加入答案，並更新：

```text 
current = bestRight
```

* 重複直到 `current >= M`。
* 最後如果成功，就輸出答案線段數量和線段內容。

What edge cases did you consider?

* 無法覆蓋 `[0, M]`
* 第一段沒有任何線段可以覆蓋到 0
* 線段左端點可能是負數
* 線段右端點可能超過 `M`
* 多條線段都能接上目前範圍，要選右端點最遠的
* 不同測資之間要有空行

## 4. Pseudocode

```text 
START
1. Read testCase.
2. For each test case:
3.     Read M.
4.     Create segments.
5.     While true:
6.         Read L and R.
7.         If L == 0 and R == 0:
8.             Stop reading segments.
9.         Add segment (L, R).
10.    Sort segments by left endpoint.
11.    Set current = 0.
12.    Set index = 0.
13.    Set possible = true.
14.    Create answer list.
15.    While current < M:
16.        bestRight = current.
17.        While index is valid and segments[index].left <= current:
18.            If segments[index].right > bestRight:
19.                bestRight = segments[index].right.
20.                bestSegment = segments[index].
21.            index++.
22.        If bestRight == current:
23.            possible = false.
24.            Break.
25.        Add bestSegment to answer.
26.        current = bestRight.
27.    If not possible:
28.        Print 0.
29.    Else:
30.        Print answer size.
31.        Print all selected segments.
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

int main()
{
    int testCase;
    cin >> testCase;

    for (int cases = 0; cases < testCase; cases++)
    {
        int M;
        cin >> M;

        vector<pair<int, int>> segments;

        while (true)
        {
            int L, R;
            cin >> L >> R;

            if (L == 0 && R == 0)
            {
                break;
            }

            segments.push_back(make_pair(L, R));
        }

        sort(segments.begin(), segments.end());

        vector<pair<int, int>> answer;

        int current = 0;
        int index = 0;
        bool possible = true;

        while (current < M)
        {
            int bestRight = current;
            pair<int, int> bestSegment;

            while (index < segments.size() && segments[index].first <= current)
            {
                if (segments[index].second > bestRight)
                {
                    bestRight = segments[index].second;
                    bestSegment = segments[index];
                }

                index++;
            }

            if (bestRight == current)
            {
                possible = false;
                break;
            }

            answer.push_back(bestSegment);
            current = bestRight;
        }

        if (cases > 0)
        {
            cout << endl;
        }

        if (!possible)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << answer.size() << endl;

            for (int i = 0; i < answer.size(); i++)
            {
                cout << answer[i].first << " " << answer[i].second << endl;
            }
        }
    }

    return 0;
}
```

Why it works:

* 程式先把所有線段依照左端點排序，方便從左到右處理。
* `current` 表示目前已經覆蓋到哪裡。
* 每一輪都只考慮左端點 `<= current` 的線段，這樣才不會產生空缺。
* 在可用線段中選右端點最大的線段，可以讓覆蓋範圍一次延伸最遠。
* 如果 `bestRight` 沒有比 `current` 更大，代表沒有線段可以繼續覆蓋，答案就是 impossible。
* 當 `current >= M` 時，代表 `[0, M]` 已經完整覆蓋。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code         | Correct Code                     |
| --------------- | ----------------- | -------------------------------- |
| Logic           | 可能隨便選可以接上的線段。     | 每次選右端點延伸最遠的線段。                   |
| Edge Cases      | 可能中間有缺口還繼續做。      | 如果無法延伸 `current`，就判斷 impossible。 |
| Output Handling | 可能忘記測資之間的空行。      | 使用 `cases > 0` 控制空行。             |
| Other           | 可能沒有排序，導致不好找可用線段。 | 先排序再用 greedy 掃描。                 |

### Reflection

我覺得最重要的是理解 `current` 的意義，它代表目前已經成功覆蓋到的位置。

每一步不是隨便選一條可以接上的線段，而是要從所有能接上的線段中，選右端點最遠的那條。
這樣才能用最少線段把覆蓋範圍往右推。

