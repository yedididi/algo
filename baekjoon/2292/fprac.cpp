#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void)
{
    int n, num = 1, level = 0;
    vector<int> sixes;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (level * 6); j++)
        {
            num++;
            if (num == n)
                break;
        }
        if (num == n)
            break;
        level++;
    }

    if (n == 1)
        cout << 1 << endl;
    else
        cout << level + 1 << endl;
}
