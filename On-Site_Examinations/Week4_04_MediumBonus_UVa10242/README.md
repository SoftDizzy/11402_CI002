# UVa 10242 - Fourth Point!!

## 1. Problem Information

Platform: UVa
Problem ID: 10242
Problem Title: Fourth Point!!
Problem Link: https://onlinejudge.org/external/102/10242.pdf
Week: 4
Date: 2026/03/17
Theme: Arrays + simulation
Category: On-site Medium (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/39_10242.cpp`

## 2. Problem Statement in My Own Words

* 這題會給四個點的座標，其中有一個點會重複出現，代表兩條邊共用同一個端點。我要利用這些點找出平行四邊形缺少的第四個點。

### What is the input?

* 輸入有多組資料。
* 每組資料有 8 個浮點數，代表 4 個點的座標：

```text
x1 y1 x2 y2 x3 y3 x4 y4
```

* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每一組輸入，輸出缺少的第四個點座標。
* 座標要輸出到小數點後三位。

### What are the main rules or constraints?

* 四個輸入點裡面會有一組座標是相同的。
* 重複的點就是兩條邊共用的端點。
* 平行四邊形可以利用向量關係來找缺少的點。
* 輸出格式要固定小數點後三位。

### What is the core task you must solve?

* 找出哪兩個點重複，然後用另外兩個不重複的點和重複點算出缺少的第四點。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
* 如果知道三個不同的點，而且其中一個是共用端點，就可以用向量加減找出第四個點。
* 這題比較麻煩的是，重複點可能出現在不同位置，不一定是固定哪兩個點相同。

### Final Strategy

* 先讀入四個點的座標。
* 檢查哪兩個點是相同的。
* 找到重複點後，把另外兩個不重複的點相加，再減掉重複點。
* 公式可以想成：

```text
answer = pointA + pointB - repeatedPoint
```

* 最後用 `fixed << setprecision(3)` 輸出答案。

What edge cases did you consider?

* 重複點可能是 `p1 == p3`
* 重複點可能是 `p1 == p4`
* 重複點可能是 `p2 == p3`
* 重複點可能是 `p2 == p4`
* 輸出要固定三位小數
* 有多組輸入，要讀到 EOF

## 4. Pseudocode



```text
START
1. While input has four points:
2.     Check which two points are the same.
3.     If p1 == p4:
4.         answer = p2 + p3 - p1.
5.     Else if p1 == p3:
6.         answer = p2 + p4 - p1.
7.     Else if p2 == p3:
8.         answer = p1 + p4 - p2.
9.     Else if p2 == p4:
10.        answer = p1 + p3 - p2.
11.    Print answer with 3 digits after decimal point.
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
No failed version was saved.
```

Why it failed:

* No failed version was saved.

### Correct Code

```cpp
#include <iostream> 
#include <iomanip>

using namespace std;

//      A - B

// 題目給平行四邊形的 相鄰的兩條邊，也就是 A B C D 這個平行四邊形   A + D = B + C               D ------ C
                                                                            //          |        |
                                                                            //      |        |          
                                                                            //   A ------ B             
int main()
{
    double x1 , x2 , x3 , x4 , y1 , y2 , y3 , y4;
    while ( cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 )
    {
        double ans_x , ans_y;
        
        // 四個點中會有一組座標相同，代表兩條邊共用的端點。
        // 可能重複的組合有：p1 == p3、p1 == p4、p2 == p3、p2 == p4。
        // 找到重複點後，答案座標 = 不重複的兩點相加 - 重複點。
        if ( x1 == x4 && y1 == y4 )                    
        {
            ans_x = x2 + x3 - x1;
            ans_y = y2 + y3 - y1;
        }
        else if ( x1 == x3 && y1 == y3 )
        {
            ans_x = x2 + x4 - x1;
            ans_y = y2 + y4 - y1;
        }
        else if ( x2 == x3 && y2 == y3 )
        {
            ans_x = x1 + x4 - x2;
            ans_y = y1 + y4 - y2;
        }
        else if ( x2 == x4 && y2 == y4 )        
        {

            ans_x = x1 + x3 - x2;
            ans_y = y1 + y3 - y2;
        }
        cout << fixed << setprecision(3) << ans_x << " " << ans_y << endl;
    }
    return 0;

}
```

Why it works:

* 程式會一直讀取四個點，直到 EOF。
* 透過 `if` 和 `else if` 判斷哪兩個點是重複點。
* 找到重複點後，就用另外兩個點相加，再減掉重複點，算出缺少的第四點。
* `fixed << setprecision(3)` 可以讓答案固定輸出到小數點後三位。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code       | Correct Code                    |
| --------------- | --------------- | ------------------------------- |
| Logic           | 可能沒有利用重複點來找第四點。 | 找出重複點後，用兩個不重複點相加再減掉重複點。         |
| Edge Cases      | 可能只判斷一種重複情況。    | 判斷四種可能的重複點組合。                   |
| Output Handling | 可能沒有輸出三位小數。     | 使用 `fixed` 和 `setprecision(3)`。 |
| Other           | 可能只處理一筆輸入。      | 使用 `while (cin >> ...)` 讀到 EOF。 |

### Reflection

這題主要是在考平行四邊形的向量關係。
一開始比較容易搞混的是哪個點要加、哪個點要減，所以要先找出重複點，再用公式處理。
