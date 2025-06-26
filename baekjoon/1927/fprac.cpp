#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n;

int main(void)
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    multiset<int> ms;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tmp;

        cin >> tmp;

        if (tmp == 0)
        {
            if (ms.empty())
                cout << "0\n";
            else
            {
                auto value = ms.begin();
                cout << *value << "\n";
                ms.erase(value);
            }
        }
        else
            ms.insert(tmp);
    }
}
