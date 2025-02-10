#include <iostream>

using namespace std;

int n;
int oneNum = 0;

int fib(int n)
{
    if (n == 1 || n == 2)
    {
        oneNum++;
        return (1);
    }
    else return (fib(n - 1) + fib(n - 2));
}

int main(void)
{
    cin >> n;
    fib(n);

    cout << oneNum << " " << n- 2 << endl;
}