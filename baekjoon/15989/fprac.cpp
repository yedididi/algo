#include <iostream>

using namespace std;

int t;
int arr[10001][3];

void makeArr(void)
{
    arr[1][0] = 1;

    arr[2][0] = 1;
    arr[2][1] = 1;

    arr[3][0] = 1;
    arr[3][1] = 1;
    arr[3][2] = 1;

    for (int i = 4; i < 10001; i++)
    {
        arr[i][0] = 1;
        arr[i][1] = arr[i - 2][0] + arr[i - 2][1];
        arr[i][2] = arr[i - 3][0] + arr[i - 3][1] + arr[i - 3][2];
    }
}

int main(void)
{
    cin >> t;

    makeArr();
    for (int i = 0; i < t; i++)
    {
        int n;

        cin >> n;
        cout << arr[n][1] + arr[n][2] + 1 << "\n";
    }
}