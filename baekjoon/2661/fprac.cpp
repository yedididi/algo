#include <iostream>

using namespace std;

int n;

void printArr(int arr[81])
{
    for (int i = 0; i < n; i++)
        cout << arr[i];
    cout << endl;
}

bool isSame(int arr[81], int startI, int dupNum, int depth)
{
    if (startI + 2 * dupNum > depth)
        return false;

    for (int i = 0; i < dupNum; i++)
    {
        if (arr[startI + i] != arr[startI + dupNum + i])
            return false;
    }
    return true;
}

bool checkIfGood(int arr[81], int depth)
{
    for (int dupNum = 1; dupNum <= ((depth / 2)); dupNum++) //(depth / 2) + 1??
    {
        for (int i = 0; i <= depth - 2 * dupNum; i++)
        {
            if (isSame(arr, i, dupNum, depth))
                return (false);
        }
    }
    return (true);
}

void backTrack(int arr[81], int depth)
{
    if (checkIfGood(arr, depth))
    {
        if (depth == n)
        {
            printArr(arr);
            exit(0);
        }
    }
    else
        return ;

    for (int i = 1; i <= 3; i++)
    {
        arr[depth] = i;
        backTrack(arr, depth + 1);
    }
}

int main(void)
{
    cin >> n;

    int arr[81] = {0, };
    backTrack(arr, 0);
}