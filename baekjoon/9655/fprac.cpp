#include <iostream>

using namespace std;

int main(void)
{
    int n;

    cin >> n;
    if ((n / 3) % 2) //now cy turn
    {
        if ((n % 3) % 2)
            cout << "CY\n";
        else
            cout << "SK\n";
    }
    else //now sk turn
    {
        if ((n % 3) % 2)
            cout << "SK\n";
        else
            cout << "CY\n";
    }
}