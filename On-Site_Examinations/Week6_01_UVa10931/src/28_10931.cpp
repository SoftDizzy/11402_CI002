#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

//  A

int main()
{
    int n;
    while ( cin >> n )
    {
        if ( n == 0 )   break;

        int count = 0;
        string s = "";                          // 字串 用來放二進位的數字
        while ( n > 0 )
        {
            int bit = n % 2;
            if ( bit == 1 )
            {
                count++;
            }
            s += char( bit + '0' );            // 轉二進位 但是還不是正確排序 要反過來
            n /= 2;
        }
        reverse ( s.begin() , s.end() );       // 反轉字串

        cout << "The parity of " << s << " is " << count << " (mod 2)." << endl;
    }
    return 0;
}
