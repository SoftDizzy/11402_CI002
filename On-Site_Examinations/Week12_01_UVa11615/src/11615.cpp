#include <iostream>
#include <algorithm>

using namespace std;

// A

int getGeneration(int x)
{
    int generation = 0;

    while (x > 0)
    {
        generation++;
        x /= 2;
    }

    return generation;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, A, B;
        cin >> N >> A >> B;

        int generationA = getGeneration(A);
        int generationB = getGeneration(B);

        int deeperGeneration = max(generationA, generationB);

        long long totalPeople = (1LL << N) - 1;

        int duplicateLevel = N - deeperGeneration;

        long long duplicatePeople = 0;

        if (duplicateLevel > 0)
        {
            duplicatePeople = 2 * ((1LL << duplicateLevel) - 1);
        }

        cout << totalPeople - duplicatePeople << endl;
    }

    return 0;
}