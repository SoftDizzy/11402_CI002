# UVa 10041 - Vito's Family

## 1. Problem Information

Platform: UVa
Problem ID: 10041
Problem Title: Vito's Family
Problem Link: https://onlinejudge.org/external/100/10041.pdf
Week: 14
Date: 2026/05/26
Theme: Sorting / Median
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/1_10041.cpp`

## 2. Problem Statement in My Own Words

* 這題會給 Vito 親戚們住的街道位置，要選一個位置讓所有親戚到這個位置的距離總和最小。
* 最後要輸出最小的距離總和。

### What is the input?

* 第一行是一個整數 `testbase`，代表有幾組測資。
* 每組測資先輸入一個整數 `n`，代表有幾個親戚。
* 接著輸入 `n` 個整數，代表每個親戚住的街道位置。

### What is the expected output?

* 每組測資輸出一個整數。
* 這個整數代表所有親戚到最佳位置的最小距離總和。

### What are the main rules or constraints?

* 要選一個位置，使所有人的距離總和最小。
* 距離使用絕對值計算。
* 對一維座標來說，讓距離總和最小的位置是 median。
* 所以只要排序後選中位數即可。

### What is the core task you must solve?

* 找出所有位置的 median，然後計算每個位置到 median 的距離總和。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可能會想每個位置都試一次，看哪個位置距離總和最小。
* 但其實這題是經典的 median 題。
* 在一條線上，要讓絕對距離總和最小，選中位數就可以。

### Final Strategy

* 先讀入測資數量。
* 每組讀入 `n` 和所有親戚的位置。
* 把位置存進 `vector<int> v`。
* 使用 `sort()` 把位置由小到大排序。
* 取中位數：

```text 
mid = v[n / 2]
```

* 接著把每個位置到 `mid` 的距離加起來：

```text 
sum += abs(v[j] - mid)
```

* 最後輸出 `sum`。

What edge cases did you consider?

* 親戚數量是奇數
* 親戚數量是偶數
* 多個親戚住在同一個位置
* 原始輸入沒有排序
* 距離要用絕對值
* 每組測資都要重新計算一次

## 4. Pseudocode

```text 
START
1. Read testbase.
2. Repeat testbase times:
3.     Read n.
4.     Create an empty vector v.
5.     Repeat n times:
6.         Read one street number.
7.         Push it into v.
8.     Sort v.
9.     mid = v[n / 2].
10.    Set sum = 0.
11.    For each number in v:
12.        sum += absolute value of number - mid.
13.    Print sum.
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
#include <algorithm>
#include <vector>

using namespace std;


// A

int main()
{
    int testbase;
    cin >> testbase;
    while ( testbase-- )
    {
        int n;
        cin >> n;
        vector <int> v;
        
        for ( int i = 0; i < n; i++ )
        {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }

        sort(v.begin(),v.end());
        int mid = v[ n / 2 ];
        int sum = 0;

        for ( int j = 0; j < n; j++ )
        {
            sum += abs ( v[j] - mid );
        }

        cout << sum << endl;
    }
}
```

Why it works:

* 排序後，`v[n / 2]` 會是中位數位置。
* 在一維座標中，中位數可以讓所有點到它的絕對距離總和最小。
* 程式用 `abs(v[j] - mid)` 計算每個親戚到中位數的距離。
* 把所有距離加總後，就是題目要求的最小距離。
* 每組測資都重新建立 `vector` 和 `sum`，不會影響下一組資料。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code              |
| --------------- | ---------------- | ------------------------- |
| Logic           | 可能用平均數或暴力嘗試所有位置。 | 使用排序後的 median。            |
| Edge Cases      | 可能沒有處理偶數個親戚。     | 直接使用 `v[n / 2]`，仍可得到最小距離。 |
| Output Handling | 可能沒有重新計算每組 sum。  | 每組測資都重新設定 `sum = 0`。      |
| Other           | 可能忘記絕對距離。        | 使用 `abs()` 計算距離。          |

### Reflection

這題讓我學到，一維座標上要讓距離總和最小，重點不是平均數，而是中位數。
平均數比較常用在平方誤差，但這題是絕對距離，所以要用 median。

只要先排序並取中位數，後面就是把所有距離加起來。

