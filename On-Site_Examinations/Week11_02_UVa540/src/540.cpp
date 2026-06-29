#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// B

int main()
{
    int teamCount;
    int scenario = 1;

    while (cin >> teamCount)
    {
        if (teamCount == 0)
        {
            break;
        }

        unordered_map<int, int> memberTeam;

        for (int i = 0; i < teamCount; i++)
        {
            int memberCount;
            cin >> memberCount;

            for (int j = 0; j < memberCount; j++)
            {
                int member;
                cin >> member;
                memberTeam[member] = i;
            }
        }

        vector<queue<int>> teamQueues(teamCount);
        queue<int> teamOrder;

        cout << "Scenario #" << scenario << endl;

        string command;

        while (cin >> command)
        {
            if (command == "STOP")
            {
                break;
            }
            else if (command == "ENQUEUE")
            {
                int member;
                cin >> member;

                int team = memberTeam[member];

                if (teamQueues[team].empty())
                {
                    teamOrder.push(team);
                }

                teamQueues[team].push(member);
            }
            else if (command == "DEQUEUE")
            {
                int team = teamOrder.front();

                cout << teamQueues[team].front() << endl;
                teamQueues[team].pop();

                if (teamQueues[team].empty())
                {
                    teamOrder.pop();
                }
            }
        }

        cout << endl;
        scenario++;
    }

    return 0;
}