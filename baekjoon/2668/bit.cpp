#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n;
vector<int> numbers(101);
int maxNum = INT_MIN;
set<int> maxNumbers;

int main(void)
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> numbers[i];
    }

    for (int i = (1 << n); i >= 0; i--)
    {
        set<int> firsts;
        set<int> seconds;
        bool different = false;

        for (int index = 0; index < n; index++)
        {
            if ((i & (1 << index)) == true)
            {
                firsts.insert(abs(index - 6));
                seconds.insert(numbers[abs(index - 6)]);
            }
        }

        int size = firsts.size();
        set<int> tmp(firsts);

        while (!firsts.empty() && !seconds.empty())
        {
            if (*firsts.begin() == *seconds.begin())
            {
                firsts.erase(*firsts.begin());
                seconds.erase(*seconds.begin());
            }
            else
                different = true;
        }

        if (different == false)
        {
            if (maxNum < size)
            {
                maxNum = size;
                maxNumbers = tmp;
            }
        }
    }

    cout << maxNum << "\n";
    for (auto itr = maxNumbers.begin(); itr != maxNumbers.end(); itr++)
    {
        cout << *itr << "\n";
    }
}