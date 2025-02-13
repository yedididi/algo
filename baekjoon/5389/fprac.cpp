#include <iostream>
#include <map>

using namespace std;

int n;
map<int, int> num;
int maxVal = -1;

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (num.find(tmp) != num.end())
            num.find(tmp)->second = num.find(tmp)->second + 1;
        else
            num.insert({tmp, 1});
    }

    map<int, int>::iterator max;
    for (map<int, int>::iterator itr = num.begin(); itr != num.end(); ++itr)
    {
        if (maxVal < itr->second)
        {
            maxVal = itr->second;
            max = itr;
        }
    }
    cout << max->first << endl;
}