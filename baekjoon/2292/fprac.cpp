#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n, level = 0, num = 0, a = 0, b = 0;
    vector<int> web[7];

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            if (level == 0)
                num = 1;
            else
            {
                num = *(--web[j].end()) + ((level - 1) * 6) + (j);
                // cout << *(--web[j].end()) << " + " << ((level - 1) * 6) << " + " <<  (j);
            }
            web[j].push_back(num);
            a = b;
            b = num;
            // cout << " = (" << a << ", " << b << ")\n"; 
            if (num > n)
                break;
        }
        if (num > n)
            break;
        level++;
    }

    if (num == 1)
        cout << "1" << endl;
    else if ((b - num) >= (num - a))
        cout << (level + (num - a)) + 1 << endl;
    else
        cout << (level + (b - num)) + 1 << endl;
}
