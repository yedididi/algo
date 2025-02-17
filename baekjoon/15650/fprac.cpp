#include <iostream>

using namespace std;

int n, m;

void printArr(int arr[100])
{
    for (int i = 0; i < m; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void makeArray(int arr[100], int depth)
{
    if (depth == m)
        printArr(arr);

    int startNum = 1;
    if (depth != 0)
        startNum = arr[depth - 1] + 1;

    for (int i = startNum; i <= n; i++)
    {
        arr[depth] = i;
        makeArray(arr, depth + 1);
    }
}

int main(void)
{
    int arr[100];
    cin >> n >> m;

    makeArray(arr, 0);
}