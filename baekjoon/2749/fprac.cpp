

#include <iostream>

using namespace std;

long long n;
long long fib[1500001];

void makeFib()
{
    fib[1] = 0;
    fib[2] = 1; 
    for (int i = 3; i < 1500001; i++)
    {
        fib[i] = (fib[i - 1] + fib[i - 2]) % 1000000;
    }
}

int main(void)
{
    cin >> n;

    makeFib();
    cout << fib[(n + 1) % 1500000] << endl;
}