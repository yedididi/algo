#include <iostream>

using namespace std;

int n;
long long fib[100];

void makeFib()
{
    fib[1] = 0;
    fib[2] = 1; 
    for (int i = 3; i < 100; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main(void)
{
    cin >> n;

    makeFib();
    cout << fib[n + 1] << endl;
}