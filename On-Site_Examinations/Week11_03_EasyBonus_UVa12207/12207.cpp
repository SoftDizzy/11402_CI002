#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

// A Bonus

int main()
{
    int P, C;
    int cases = 1;

    while (cin >> P >> C)
    {
        if (P == 0 && C == 0)
        {
            break;
        }

        deque<int> q;

        int limit = min(P, C);

        for (int i = 1; i <= limit; i++)
        {
            q.push_back(i);
        }

        cout << "Case " << cases << ":" << endl;

        for (int i = 0; i < C; i++)
        {
            char command;
            cin >> command;

            if (command == 'N')
            {
                int person = q.front();
                q.pop_front();
                q.push_back(person);

                cout << person << endl;
            }
            else if (command == 'E')
            {
                int person;
                cin >> person;

                for (deque<int>::iterator it = q.begin(); it != q.end(); it++)
                {
                    if (*it == person)
                    {
                        q.erase(it);
                        break;
                    }
                }

                q.push_front(person);
            }
        }

        cases++;
    }

    return 0;
}