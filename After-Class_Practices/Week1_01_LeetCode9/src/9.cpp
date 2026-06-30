#include <iostream>

using namespace std;

// After-Class Practice
// LeetCode 9 - Palindrome Number

class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
        {
            return false;
        }

        if (x != 0 && x % 10 == 0)
        {
            return false;
        }

        int reversedHalf = 0;

        while (x > reversedHalf)
        {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }

        return x == reversedHalf || x == reversedHalf / 10;
    }
};

int main()
{
    Solution sol;

    int x;

    while (cin >> x)
    {
        if (sol.isPalindrome(x))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }

    return 0;
}