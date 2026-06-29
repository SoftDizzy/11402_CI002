#include <iostream>
#include <string>
#include <list>

using namespace std;

// B Bonus

int main()
{
    string line;

    while (getline(cin, line))
    {
        list<char> text;
        list<char>::iterator cursor = text.end();

        for (int i = 0; i < line.size(); i++)
        {
            char c = line[i];

            if (c == '[')
            {
                cursor = text.begin();
            }
            else if (c == ']')
            {
                cursor = text.end();
            }
            else
            {
                text.insert(cursor, c);
            }
        }

        for (list<char>::iterator it = text.begin(); it != text.end(); it++)
        {
            cout << *it;
        }

        cout << endl;
    }

    return 0;
}