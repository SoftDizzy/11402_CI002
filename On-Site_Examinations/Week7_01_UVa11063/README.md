# UVa 11063 - B2-Sequence

## 1. Problem Information

Platform: UVa
Problem ID: 11063
Problem Title: B2-Sequence
Problem Link: https://onlinejudge.org/external/110/11063.pdf
Week: 7
Date: 2026/04/07
Theme: Binary search
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/23_11063.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個數列，要判斷它數列要是正數、嚴格遞增，而且任兩個數字相加的結果不能重複。

### What is the input?

* 輸入有多組資料。
* 每組資料先有一個整數 `n`，代表數列長度。
* 接著輸入 `n` 個整數。

### What is the expected output?

* 每組資料要輸出：

```text
Case #x: It is a B2-Sequence.
```

或

```text
Case #x: It is not a B2-Sequence.
```

* 每組輸出後要再空一行。

### What are the main rules or constraints?

* 數列中的數字必須是正整數。
* 數列要嚴格遞增，也就是後面的數字一定要比前面大。
* 對所有 `i <= j`，`b[i] + b[j]` 的結果不能重複。
* 每組測資都要有 Case 編號。

### What is the core task you must solve?

* 檢查數列是否符合 B2-Sequence 的定義，尤其是所有兩數和不能有重複。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始先想到要檢查兩個條件：數列本身是否合法，以及兩個數字相加後有沒有重複。
* 數列合法的部分可以直接檢查是不是正數和嚴格遞增。
* 兩數和的部分可以用雙層迴圈枚舉所有 `v[i] + v[j]`，再用陣列或布林表記錄有沒有出現過。

### Final Strategy

* 讀入 `n` 和數列。
* 用 `ok` 記錄目前是否還符合條件。
* 讀入時先檢查有沒有負數。
* 再檢查數列是否嚴格遞增，如果 `v[i] >= v[i+1]` 就不符合。
* 建立 `used` 布林陣列，記錄某個 sum 是否出現過。
* 用雙層迴圈跑所有 `i <= j` 的組合。
* 如果某個 sum 已經出現過，就代表不是 B2-Sequence。
* 最後按照 `ok` 的結果輸出答案。

What edge cases did you consider?

* 數列不是嚴格遞增
* 數列裡有非正整數
* 兩數和重複
* `i` 和 `j` 可以是同一個位置
* 有多組測資，要輸出 Case 編號
* 每組輸出後要空一行

## 4. Pseudocode

```text
START
1. Set cases = 1.
2. While input has n:
3.     Read n numbers into vector v.
4.     Set ok = true.
5.     If any number is not positive:
6.         Set ok = false.
7.     For i from 0 to n - 2:
8.         If v[i] >= v[i + 1]:
9.             Set ok = false.
10.    Create used array and set all values to false.
11.    For i from 0 to n - 1:
12.        For j from i to n - 1:
13.            sum = v[i] + v[j].
14.            If used[sum] is true:
15.                Set ok = false.
16.            Else:
17.                Set used[sum] = true.
18.    Print result for this case.
19.    Print blank line.
20.    Increase cases by 1.
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

//      B

int main()
{
    int n;
    int cases = 1;

    while (cin >> n)
    {
        vector<int> v(n);
        bool ok = true;
        for ( int i = 0; i < n; i++ )
        {
            cin >> v[i];
            if ( v[i] < 0 )
                ok = false;
        }

    

        // 檢查是否為正整數且嚴格遞增
        for ( int i = 0; i < n - 1; i++ )
        {
            if ( v[i] >= v[i+1] )
            {
                ok = false;
            }
        }

        // 檢查所有 bi + bj 是否重複
   
        vector<bool> used(20005, false);

        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                int sum = v[i] + v[j];

                if (used[sum] == true)  // 若標記過了 代表重複了
                {
                    ok = false;
                }
                else
                {
                    used[sum] = true;   // 還沒重複 所以標記
                }
            }
        }

        cout << "Case #" << cases << ": ";

        if (ok)
        {
            cout << "It is a B2-Sequence." << endl;
        }
        else
        {
            cout << "It is not a B2-Sequence." << endl;
        }

        cout << endl;

        cases++;
    }

    return 0;
}
```

Why it works:

* 程式會讀到 EOF，可以處理多組測資。
* 先檢查數列是否符合基本條件，包含數字不能小於 0，以及要嚴格遞增。
* 使用雙層迴圈枚舉所有 `v[i] + v[j]`，其中 `j` 從 `i` 開始，所以有包含 `i == j` 的情況。
* 用 `used[sum]` 記錄某個和是否已經出現過。
* 只要發現重複的和，就把 `ok` 設成 false。
* 最後依照題目格式輸出 Case 結果和空行。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code          | Correct Code               |
| --------------- | ------------------ | -------------------------- |
| Logic           | 可能只檢查數列遞增，沒有檢查兩數和。 | 同時檢查遞增和所有兩數和是否重複。          |
| Edge Cases      | 可能忘記 `i == j` 的組合。 | 內層迴圈從 `j = i` 開始，有包含自己加自己。 |
| Output Handling | 可能少了 Case 編號或空行。   | 使用 `Case #x:` 格式，並在每組後空一行。 |
| Other           | 可能沒有記錄出現過的 sum。    | 使用 `used` 陣列標記每個 sum。      |

### Reflection

這題重點是看懂 B2-Sequence 的定義。
不是只要數列遞增就好，還要所有 `bi + bj` 的結果都不能重複。

我覺得這題比較容易漏掉的是 `i == j` 也要算，例如第一個數字可以自己加自己。
所以雙層迴圈的內層要從 `i` 開始，不是從 `i + 1` 開始。

