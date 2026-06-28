# UVa 10420 - List of Conquests

## 1. Problem Information

Platform: UVa
Problem ID: 10420
Problem Title: List of Conquests
Problem Link: https://onlinejudge.org/external/104/10420.pdf
Week: 5
Date: 2026/03/24
Theme: Sorting basics
Category: On-site Easy (Bonus)
Source Code (Fail): No failed version was saved
Source Code (Correct/Accepted): `src/7_10420.cpp`

## 2. Problem Statement in My Own Words

* 這題會給很多筆資料，每筆資料的第一個字是國家名稱，後面是人名。要統計每個國家出現幾次，最後按照國家名稱字母順序輸出。

### What is the input?

* 第一行是一個整數 `testbase`，代表有幾筆資料。
* 接下來每一行會先有一個國家名稱，後面接著一個人名。
* 人名可能包含空白，但這題只需要統計國家，所以後面的人名可以不用處理。

### What is the expected output?

* 輸出每個國家名稱和出現次數。
* 每個國家輸出一行：

```text
country count
```

* 國家名稱要依照字母順序排列。

### What are the main rules or constraints?

* 只需要看每一行的國家名稱。
* 同一個國家出現多次時，要累加次數。
* 後面的人名不影響答案。
* 輸出時要按照國家名稱排序。

### What is the core task you must solve?

* 核心任務是統計每個國家出現的次數，並按照國家名稱排序後輸出。

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

* 我一開始想到可以用 `map` 來存國家和出現次數。
* 因為 `map` 會自動按照 key 排序，所以最後輸出時就不用自己再排序一次。
* 這題比較要注意的是，讀完國家後，後面的人名要用 `getline` 讀掉，不然會影響下一筆輸入。

### Final Strategy

* 先讀入資料筆數 `testbase`。
* 建立 `map<string, int> list` 來記錄每個國家的次數。
* 每筆資料先用 `cin >> country` 讀國家名稱。
* 再用 `getline(cin, people)` 把後面的人名讀掉。
* 每讀到一次國家，就讓 `list[country]++`。
* 最後用 range-based for 迴圈輸出 map 裡面的資料。

What edge cases did you consider?

* 同一個國家出現很多次
* 人名可能有空白
* 國家名稱需要照字母順序輸出
* 只需要統計國家，不需要處理人名內容
* 輸出格式是國家名稱加空格再加次數

## 4. Pseudocode

```text
START
1. Read testbase.
2. Create a map to store country counts.
3. Repeat testbase times:
4.     Read country.
5.     Read the rest of the line as people.
6.     Add 1 to the count of country.
7. For each country in the map:
8.     Print country and its count.
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
#include <map>

using namespace std;

// A 

int main()
{
    int testbase;
    cin >> testbase;
    map < string , int > list;
    while ( testbase-- )
    {
        string country;
        cin >> country;

        string people;
        getline ( cin , people );

        list[country]++;
        
    }

    for ( auto i : list )
    {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}
```

Why it works:

* 程式使用 `map<string, int>` 統計每個國家出現的次數。
* `cin >> country` 只讀取每行的第一個字，也就是國家名稱。
* `getline(cin, people)` 把後面的人名讀掉，避免影響下一筆輸入。
* `map` 會自動按照國家名稱排序，所以最後直接輸出就符合題目要求。

## 6. Difference and Reflection

### Key Differences

| Item            | Fail Code      | Correct Code        |
| --------------- | -------------- | ------------------- |
| Logic           | 可能沒有正確累加每個國家。  | 使用 `map` 記錄國家和次數。   |
| Edge Cases      | 可能被後面的人名和空白影響。 | 用 `getline` 讀掉人名部分。 |
| Output Handling | 可能沒有排序輸出。      | `map` 會自動依照國家名稱排序。  |
| Other           | 可能把整行都當成 key。  | 只把國家名稱當成 key。       |

### Reflection

這題主要是在練習統計資料和排序輸出。
我覺得用 `map` 很適合，因為它可以同時處理「計數」和「依照 key 排序」。

這題比較容易忽略的是人名那一段。
雖然題目會給完整名字，但答案只需要國家，所以我用 `getline` 把剩下的字串讀掉。

