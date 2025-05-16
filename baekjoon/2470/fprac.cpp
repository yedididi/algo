#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> arr;
int leftIndex, rightIndex, sum;
int minValueLeftIndex, minValueRightIndex, minSum = 2147483647;

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }

    sort(arr.begin(), arr.end());

    leftIndex = 0;
    rightIndex = n - 1;
    sum = arr[0] + arr[n - 1];

    minValueLeftIndex = 0;
    minValueRightIndex = n - 1;
    minSum = arr[0] + arr[n - 1];

    while (1)
    {
        // cout << "left is:" << arr[leftIndex] << "right is:" << arr[rightIndex] << endl;
        // if (rightIndex <= leftIndex)
        //     break;

        if ((arr[leftIndex] + arr[rightIndex]) > 0)
            rightIndex--;
        else
            leftIndex++;

        if (rightIndex <= leftIndex)
            break;

        if (abs(arr[rightIndex] + arr[leftIndex]) < abs(minSum))
        {
            // cout << "minSum is:" << minSum << endl;
            minSum = arr[rightIndex] + arr[leftIndex];
            minValueLeftIndex = leftIndex;
            minValueRightIndex = rightIndex;
        }
    }
    cout << arr[minValueLeftIndex] << " " << arr[minValueRightIndex] << endl;
}

// 5
// -2 4 -1 98 102

// 5
// -111111 -11111 -2 -1 99999999