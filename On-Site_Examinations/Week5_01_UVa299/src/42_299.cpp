#include <iostream>
#include <vector>

using namespace std;

//      A

int main()
{
    int testbase;
    cin >> testbase;

    while (testbase--)
    {
        int n;
        cin >> n;

        vector<int> v(n);

        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        int count = 0;
                                                            // Bubble Sort 就是雙層迴圈，反覆比較相鄰兩個元素，順序錯就交換。
        for (int pass = 0; pass < n - 1; pass++)            // 遇到bubble sort 可以用雙層迴圈搞定   最多只要多做 n - 1 輪 就可以完成
        {
            for (int i = 0; i < n - 1; i++)
            {
                if (v[i] > v[i + 1])
                {
                    int temp = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = temp;

                    count++;
                }
            }
        }

        cout << "Optimal train swapping takes " << count << " swaps." << endl;
    }

    return 0;
}