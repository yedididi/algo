#include <iostream>
#include <cmath>

using namespace std;

/*
    0 0
    1 1

    2 10
    3 11

    4 100
    5 101
    6 110
    7 111

    8  1000
    9  1001
    10 1010
    11 1011
    12 1100
    13 1101
    14 1110
    15 1111

    16 10000
*/

int main(void)
{
    long long sum = 0;
    long long a, b;
    cin >> a >> b;
    long long answers[10000000000000000];
    long long powerOfTwo = 2;

    answers[0] = 0;
    answers[1] = 1;

    for (long long index = 2; index <= b; index++)
    {
        if (index == powerOfTwo)
        {
            powerOfTwo *= 2;
            answers[index] = 1;
        }
        else
        {
            answers[index] = answers[index - (powerOfTwo / 2)] + 1;
        }
    }
    cout << sum << endl;
}