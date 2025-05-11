#include <iostream>
#include <vector>

using namespace std;

int n;

bool isValue(int input)
{
    int sum = 0;
    int num = input;

    while (num)
    {
        if (num / 10)
        {
            sum += (num % 10);
            num = num / 10;
        }
        else
        {
            sum += num;
            break;
        }
    }

    if (n == (input + sum))
        return (true);
    return (false);
}

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        if (isValue(i))
        {
            cout << i << endl;
            return (0);
        }
    }
    cout << 0 << endl;
}
