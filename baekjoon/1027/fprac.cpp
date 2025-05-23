#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

vector<int> buildings;

bool checkInSight(int myBuilding, int otherBuilding)
{
    int start = otherBuilding, end = myBuilding;
    if (myBuilding < otherBuilding)
    {
        start = myBuilding;
        end = otherBuilding;
    }

    for (int k = start + 1; k < end; k++)
    {
        long long kHeight = 1LL * (otherBuilding - myBuilding) * buildings[k];
        long long graphValue = (1LL * (buildings[otherBuilding] - buildings[myBuilding]) * (k - myBuilding)) + (1LL * buildings[myBuilding] * (otherBuilding - myBuilding));

        // cout << "kHeight is:" << kHeight << ", graphValue is:" << graphValue << endl;

        if (abs(kHeight) >= abs(graphValue))
            return (false);
    }
    return (true);
}

int main(void)
{
    int n;
    int maxSum = INT_MIN;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        buildings.push_back(tmp);
    }

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (checkInSight(i, j) == true)
                sum++;
        }
        // cout << "i is:" << i << ", sum is:" << sum << endl;
        maxSum = max(maxSum, sum);
    }
    cout << maxSum << endl;
}