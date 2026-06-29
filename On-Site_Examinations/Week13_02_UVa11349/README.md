# UVa 11349 - Symmetric Matrix

## 1. Problem Information

Platform: UVa
Problem ID: 11349
Problem Title: Symmetric Matrix
Problem Link: https://onlinejudge.org/external/113/11349.pdf
Week: 13
Date: 2026/05/19
Theme: 2D Array
Category: On-site Medium
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/21_11349.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個 `n x n` 的矩陣，要判斷它是不是 symmetric matrix。
* 題目要求矩陣中的數字不能是負數，而且從左上到右下攤平成一維後，要和反方向的位置相同。

### What is the input?

* 第一行是一個整數 `testbase`，代表有幾組測資。
* 每組測資會先輸入類似：

```text 
N = n
```

* 接著會輸入 `n * n` 個數字，代表矩陣內容。

### What is the expected output?

* 每組測資要輸出：

```text 
Test #x: Symmetric.
```

或

```text 
Test #x: Non-symmetric.
```

其中 `x` 是測資編號。

### What are the main rules or constraints?

* 矩陣不能有負數。
* 如果有任何一個數字小於 0，直接不是 symmetric。
* 矩陣攤平成一維後，前後對稱的位置要相同。
* 也就是 `v[i]` 要等於 `v[total - 1 - i]`。

### What is the core task you must solve?

* 檢查矩陣是否符合對稱條件，並確認所有數字都不是負數。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 一開始可以用二維陣列存矩陣，再檢查 `(i, j)` 和 `(n - 1 - i, n - 1 - j)`。
* 但這份 code 用一維 `vector` 存全部數字，這樣也可以。
* 因為矩陣如果是對中心對稱，攤平成一維後，前後位置剛好可以互相比較。

### Final Strategy

* 先讀入測資數量。
* 每組讀入 `N = n`，其中 `N` 和 `=` 用 `char` 接掉。
* 用 `vector<long long> v` 存 `n * n` 個數字。
* 讀入時如果發現數字小於 0，就把 `sym` 設成 false。
* 讀完後，令 `total = n * n`。
* 從 `0` 檢查到 `total / 2`：

  * 比較 `v[i]` 和 `v[total - 1 - i]`。
  * 如果不同，就不是 symmetric。
* 最後依照 `sym` 輸出結果。

What edge cases did you consider?

* 矩陣中有負數
* 矩陣大小是 `1 x 1`
* 數字很大，所以使用 `long long`
* 前後對稱位置不相同
* 輸出格式中的 `Test #x:` 要正確
* 每組測資都要重新判斷一次

## 4. Pseudocode

```text 
START
1. Read testbase.
2. Set count = 1.
3. Repeat testbase times:
4.     Read characters and n from "N = n".
5.     Create an empty vector v.
6.     Set sym = true.
7.     Repeat n * n times:
8.         Read num.
9.         If num < 0:
10.            Set sym = false.
11.        Push num into v.
12.    total = n * n.
13.    For i from 0 to total / 2 - 1:
14.        If v[i] != v[total - 1 - i]:
15.            Set sym = false.
16.            Break.
17.    Print "Test #count: ".
18.    If sym is true:
19.        Print "Symmetric."
20.    Else:
21.        Print "Non-symmetric."
22.    count++.
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

// B

int main()
{
    int testbase;
    cin >> testbase;

    int count = 1;

    while ( testbase-- )
    {
        char a,b;
        long long n;
        cin >> a >> b >> n;

        vector<long long> v;    // 注意要用long long
        bool sym = true;

        for ( int i = 0; i < n * n; i++ )
        {
            long long num;
            cin >> num;

            if ( num < 0 )
            {
                sym = false;
            }
            v.push_back(num);
        }

        int total = n * n;

        for ( int i = 0; i < total / 2; i++ )
        {
            if ( v[i] != v[ total - 1 - i ] )
            {
                sym = false;
                break;
            }
            
        } 
                
        cout << "Test #" << count << ": ";
                     
        if ( sym == true )         
        {                 
            cout << "Symmetric." << endl;              
        }      
        else      
        {          
            cout << "Non-symmetric." << endl;      
        }
            
        
        count++;
    }
    return 0;
}
```

Why it works:

* 程式用 `vector<long long>` 存下整個矩陣內容，可以處理較大的數字。
* 讀入時會檢查是否有負數，只要有負數就不是 symmetric。
* 矩陣攤平成一維後，對稱位置會是 `i` 和 `total - 1 - i`。
* 只需要檢查前半段，因為後半段會被前半段對應到。
* 如果全部符合，而且沒有負數，就輸出 `Symmetric.`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code        | Correct Code                                          |
| --------------- | ---------------- | ----------------------------------------------------- |
| Logic           | 可能只檢查矩陣左右或上下。    | 把矩陣攤平成一維後檢查前後對稱。                                      |
| Edge Cases      | 可能忘記負數不能出現。      | 讀入時只要 `num < 0` 就標記為 false。                           |
| Output Handling | 可能格式不符合題目。       | 使用 `Test #x: Symmetric.` 或 `Test #x: Non-symmetric.`。 |
| Other           | 可能使用 int 導致數字不夠。 | 使用 `long long` 儲存矩陣元素。                                |

### Reflection

我覺得這題最容易漏掉的是負數條件。
就算矩陣前後對稱，只要裡面有負數，也要輸出 `Non-symmetric.`。

