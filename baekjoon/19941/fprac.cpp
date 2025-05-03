#include <iostream>
#include <vector>

using namespace std;

int n, k, count = 0;
vector<char> table(20000, 0);

int checkForPerson(int index)
{
    int startIndex = 0, endIndex = n - 1;

    if (index - k > 0)
        startIndex = index - k;
    if (index + k < n)
        endIndex = index + k;

    for (int i = startIndex; i <= endIndex; i++)
    {
        if (table[i] == 'P')
        {
            count++;
            return (i);
        }
    }
    return (-1);
}

int main(void)
{
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> table[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (table[i] == 'H')
        {
            int p = checkForPerson(i);
            if (p != -1)
                table[p] = 'T';
        }
    }
    cout << count << endl;
}