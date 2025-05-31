#include <iostream>
#include <cmath>

using namespace std;

long long getMaxLength(long long num)
{
    long long powerOfTwo = 0;

    while (1)
    {
        if (num < pow(2, powerOfTwo))
            break;
        else
            powerOfTwo++;
    }
    return (powerOfTwo);
}

int main(void)
{
    long long sum = 0;
    long long a, b;
    cin >> a >> b;

    for (int num = a; num <= b; num++)
    {
        long long maxLength = getMaxLength(num);
        for (long long shiftNum = 0; shiftNum <= maxLength; shiftNum++)
        {
            if (num & (1 << shiftNum))
                sum++;
        }
    }
    cout << sum << endl;
}