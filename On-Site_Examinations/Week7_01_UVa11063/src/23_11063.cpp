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

    

        // 條件一：檢查是否為正整數且嚴格遞增
        for ( int i = 0; i < n - 1; i++ )
        {
            if ( v[i] >= v[i+1] )
            {
                ok = false;
            }
        }

        // 條件二：檢查所有 bi + bj 是否重複
   
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