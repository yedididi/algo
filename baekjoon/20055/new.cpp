#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    int n, k, beltStart = 0, beltEnd, zeroDurability = 0, level = 0;

    cin >> n >> k;

    beltEnd = n - 1;
    vector<pair<int, bool>> belt(2 * n, make_pair(0, false));
    for (int i = 0; i < (2 * n); i++)
        cin >> belt[i].first;

    while (1)
    {
        level++;

        //rotate belt
        beltStart = ((beltStart + (2 * n) - 1) % (2 * n));
        beltEnd = ((beltEnd + (2 * n) - 1) % (2 * n));
        if (belt[beltEnd].second) //if a robot exists in end belt
            belt[beltEnd].second = false; //take it off

        //moveRobot
        int current = beltEnd;
        int stop = (beltStart + (2 * n) - 1) % (2 * n);
        while (current != stop)
        {
            int next = (current + 1) % (2 * n);
            if (!belt[next].second && belt[current].second && belt[next].first > 0)
            {
                belt[next].second = true;
                belt[next].first--;
                belt[current].second = false;

                if (belt[next].first == 0)
                    zeroDurability++;
            }
            current = (current + (2 * n) - 1) % (2 * n);  // safe backward move
        }
        if (belt[beltEnd].second) //if a robot exists in end belt
            belt[beltEnd].second = false; //take it off

        //putRobot
        if (belt[beltStart].first) //if a robot's durability is bigger than 0
        {
            belt[beltStart].second = true; //put robot
            belt[beltStart].first--;

            if (belt[beltStart].first == 0)
                zeroDurability++;
        }

        if (zeroDurability >= k)
            break;
    }

    cout << level << endl;
}