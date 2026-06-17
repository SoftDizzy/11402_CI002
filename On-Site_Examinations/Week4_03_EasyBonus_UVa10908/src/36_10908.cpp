#include <iostream>
#include <vector>
#include <string>

/*
    給你矩陣大小與字母，以及 q 個 測試中心點以及座標，要你算出中心點往外擴張後，若範圍內的字母都與中心點一的話就是符合題目要求，並要你算出最大擴張後的方形大小
*/
using namespace std;

//      B

int main()
{
    int testbase;
    cin >> testbase;    //幾組側資

    while (testbase--)
    {
        int m, n, q;                // m 個 row ， n 個 column ， q 個中心點
        cin >> m >> n >> q;

        vector<string> v(m);        // 設個陣列 大小為 m ( row )

        for (int i = 0; i < m; i++) // 依序往下讀取 row    v[0] = "aaaabbbbcc"
        {
            cin >> v[i];            // cin column         v[1] = "aacccbbbbb"
        }

        cout << m << " " << n << " " << q << endl;

        while (q--)                // 幾個中心點
        {
            int r, c;              // 中心座標
            cin >> r >> c;

            char target = v[r][c];

            int length = 1;         // 最小就是 1 

            for (int k = 1; ; k++)  // 設置擴張的大小 從 1　開始
            {
                int top = r - k;    // 設置擴張方形的邊界  要記住 這題的起始點是左上， ( m , n )是在右下角
                int bottom = r + k;
                int left = c - k;
                int right = c + k;

                if (top < 0 || bottom >= m || left < 0 || right >= n)       // 測試是否有邊界問題
                {
                    break;
                }

                bool ok = true;

                for (int i = top; i <= bottom; i++)
                {
                    for (int j = left; j <= right; j++)
                    {
                        if (v[i][j] != target)                 // 測試方形裡面是不是都與中心一樣
                        {
                            ok = false;
                            break;
                        }
                    }

                    if (ok == false)
                    {
                        break;
                    }
                }

                if (ok == true)
                {
                    length = 2 * k + 1;
                }
                else
                {
                    break;
                }
            }

            cout << length << endl;
        }
    }

    return 0;
}