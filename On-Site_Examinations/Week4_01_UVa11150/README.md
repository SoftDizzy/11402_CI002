# UVa 11150 - Cola

## 1. Problem Information

Platform: UVa
Problem ID: 11150
Problem Title: Cola
Problem Link: https://onlinejudge.org/external/111/11150.pdf
Week: 4
Date: 2026/03/17
Theme: Arrays + simulation
Category: On-site Easy
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/48_11150.cpp`

## 2. Problem Statement in My Own Words

* 這題會給一個整數 `n`，代表一開始有幾瓶可樂。喝完後會得到空瓶，每 3 個空瓶可以換 1 瓶新的可樂，問最多可以喝到幾瓶。

### What is the input?

* 輸入有多筆資料。
* 每筆資料是一個整數 `n`。
* 程式要一直讀到 EOF 為止。

### What is the expected output?

* 對每一個 `n`，輸出最多可以喝到的可樂總瓶數。
* 每筆答案輸出一行。

### What are the main rules or constraints?

* 一開始可以先喝掉 `n` 瓶，所以總數先是 `n`。
* 喝完後會有 `n` 個空瓶。
* 每 3 個空瓶可以換 1 瓶新的可樂。
* 新換來的可樂喝完後，也會再產生空瓶。
* 如果最後剩下 2 個空瓶，可以借 1 個空瓶再換 1 瓶，所以答案可以多加 1。

### What is the core task you must solve?

* 核心任務是模擬空瓶換可樂的過程，計算總共最多能喝幾瓶。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始的想法是直接模擬換瓶子的過程。
* 因為每次都是 3 個空瓶換 1 瓶，所以只要空瓶數量大於等於 3，就可以繼續換。
* 這題比較特別的是最後如果剩 2 個空瓶，還可以多喝 1 瓶。

### Final Strategy

* 讀入 `n`。
* 設定 `total = n`，代表已經喝到的總瓶數。
* 設定 `empty = n`，代表目前手上的空瓶數。
* 當 `empty >= 3` 時：

  * `newCola = empty / 3`，算出可以換幾瓶新的。
  * 把 `newCola` 加到 `total`。
  * 更新空瓶數為 `empty % 3 + newCola`。
* 迴圈結束後，如果 `empty == 2`，代表可以借一個空瓶再多換一瓶，所以 `total++`。
* 最後輸出 `total`。

What edge cases did you consider?

* `n` 很小，例如 1 或 2
* 空瓶剛好可以被 3 整除
* 最後剩下 1 個空瓶，不能再換
* 最後剩下 2 個空瓶，可以多喝 1 瓶
* 有多筆輸入，要讀到 EOF

## 4. Pseudocode

```
START
1. While input has n:
2.     Set total = n.
3.     Set empty = n.
4.     While empty >= 3:
5.         newCola = empty / 3.
6.         Add newCola to total.
7.         empty = empty % 3 + newCola.
8.     If empty == 2:
9.         Add 1 to total.
10.    Print total.
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

using namespace std;


//      A

int main()
{
    int n;

    while (cin >> n)
    {
        int total = n;
        int empty = n;

        while (empty >= 3)
        {
            int newCola = empty / 3;
            total += newCola;

            empty = empty % 3 + newCola;
        }

        if (empty == 2)
        {
            total++;
        }

        cout << total << endl;
    }

    return 0;
}
```

Why it works:

* 程式可以用 EOF 讀取多筆資料。
* `total` 記錄目前總共喝了幾瓶。
* `empty` 記錄目前剩下幾個空瓶。
* 每次用 `empty / 3` 算可以換幾瓶，再把新可樂喝完後產生的空瓶加回去。
* 最後如果剩 2 個空瓶，依照題目規則可以再多喝 1 瓶，所以 `total++`。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code           | Correct Code                   |
| --------------- | ------------------- | ------------------------------ |
| Logic           | 可能只算一次換瓶。           | 持續模擬到空瓶少於 3。                   |
| Edge Cases      | 可能忘記剩 2 個空瓶的情況。     | `empty == 2` 時多加 1。            |
| Output Handling | 可能只處理一筆資料。          | 使用 `while (cin >> n)` 讀到 EOF。  |
| Other           | 可能沒有把新換來的瓶子喝完後再變空瓶。 | 用 `empty % 3 + newCola` 更新空瓶數。 |

### Reflection

重點是不要只換一次，要一直換到不能換為止。
我覺得最容易忘記的是最後剩 2 個空瓶可以多喝 1 瓶。

這題讓我練習用變數分開記錄「已經喝的總數」和「目前剩下的空瓶」。
