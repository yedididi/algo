#include <iostream>
#include <vector>

using namespace std;

vector<int> arr(20, 0);

char signInOrder[3] = {' ', '+', '-'};

bool checkSumZero(int depth)
{
    int sum = 1;

    for (int i = 0; i < depth; i++)
    {
        if (arr[i] == '+')
            sum = sum + (i + 2);
        else if (arr[i] == '-')
            sum = sum - (i + 2);
    }
    if (sum == 0)
        return (true);
    return (false);
}

void brute(int endNumber, int depth, int number)
{
    if (depth == ((endNumber * 2) - 1))
    {
        if (checkSumZero(depth))
            printArr();
    }

    for (int i = 0; i < 3; i++)
    {
        if (signInOrder[i] == ' ')
        {
            arr[depth] = (number * 10) + (number + 1);
            brute(endNumber, depth + 1, number + 2);
        }
        else
        {
            arr[depth] = number;
            arr[depth + 1] = signInOrder[i];
            brute(endNumber, depth + 2, number + 1);
        }
    }
}

int main(void)
{
    int n;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int number;

        cin >> number;

        arr.clear();
        brute(number, 0, 1);
    }
}