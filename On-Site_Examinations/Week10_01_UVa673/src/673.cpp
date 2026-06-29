#include <iostream>
#include <string>
#include <stack>

using namespace std;

// A

int main()
{
    int testCase;
    cin >> testCase;
    cin.ignore();

    while (testCase--)
    {
        string s;
        getline(cin, s);

        stack<char> st;
        bool ok = true;

        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];

            if (c == '(' || c == '[')
            {
                st.push(c);
            }
            else if (c == ')')
            {
                if (st.empty() || st.top() != '(')
                {
                    ok = false;
                    break;
                }
                st.pop();
            }
            else if (c == ']')
            {
                if (st.empty() || st.top() != '[')
                {
                    ok = false;
                    break;
                }
                st.pop();
            }
        }

        if (ok && st.empty())
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}