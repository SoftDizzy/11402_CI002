#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// B Bonus

string sourceWord, targetWord;
vector<char> operations;

void dfs(int sourceIndex, int targetIndex, stack<char> st)
{
    int n = sourceWord.size();

    if (targetIndex == n)
    {
        for (int i = 0; i < operations.size(); i++)
        {
            if (i > 0)
            {
                cout << " ";
            }
            cout << operations[i];
        }
        cout << endl;
        return;
    }

    // push operation: take next character from sourceWord
    if (sourceIndex < n)
    {
        st.push(sourceWord[sourceIndex]);
        operations.push_back('i');

        dfs(sourceIndex + 1, targetIndex, st);

        operations.pop_back();
        st.pop();
    }

    // pop operation: stack top must match targetWord[targetIndex]
    if (!st.empty() && st.top() == targetWord[targetIndex])
    {
        char topChar = st.top();
        st.pop();
        operations.push_back('o');

        dfs(sourceIndex, targetIndex + 1, st);

        operations.pop_back();
        st.push(topChar);
    }
}

int main()
{
    while (cin >> sourceWord >> targetWord)
    {
        cout << "[" << endl;

        string a = sourceWord;
        string b = targetWord;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if (sourceWord.size() == targetWord.size() && a == b)
        {
            stack<char> st;
            operations.clear();

            dfs(0, 0, st);
        }

        cout << "]" << endl;
    }

    return 0;
}