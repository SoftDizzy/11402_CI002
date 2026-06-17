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