#include <iostream>
#include <string>
#include <vector>

using namespace std;

// B

int main()
{
    int testCase;
    cin >> testCase;

    while ( testCase-- )
    {
        int n;
        cin >> n;

        vector<int> instructions;
        int position = 0;

        for ( int i = 0; i < n; i++ )
        {
            string command;
            cin >> command;

            if ( command == "LEFT" )
            {
                instructions.push_back(-1);
                position--;
            }
            else if ( command == "RIGHT" )
            {
                instructions.push_back(1);
                position++;
            }
            else
            {
                string asText;
                int index;
                cin >> asText >> index;

                int move = instructions[index - 1];
                instructions.push_back(move);
                position += move;
            }
        }

        cout << position << endl;
    }

    return 0;
}