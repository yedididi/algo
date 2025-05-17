#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers;

int getSum(int mid)
{
    int sum = 0;

    for (vector<int>::iterator itr = numbers.begin(); itr != numbers.end(); itr++)
    {
        if (*itr <= mid)
            sum += *itr;
        else
            sum += mid;
    }
    return (sum);
}

int main(void)
{
    int n, budget;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tmp;

        cin >> tmp;
        numbers.push_back(tmp);
    }
    cin >> budget;

    sort(numbers.begin(), numbers.end());

    int start = 0;
    int end = *(--numbers.end());
    int mid = (start + end) / 2;
    int maxSum = 0;
    int answer = 0;

    while (1)
    {
        int tmpSum = getSum(mid);

        // cout << "this is mid:" << mid << ", this is sum:" << tmpSum << endl;

        if (tmpSum > budget)
        {
            end = mid - 1;
            mid = (start + end) / 2;
        }
        else if (tmpSum < budget)
        {
            if (abs(maxSum - budget) > abs(tmpSum - budget))
            {
                maxSum = tmpSum;
                answer = mid;
            }
            start = mid + 1;
            mid = (start + end) / 2;
        }
        else
        {
            maxSum = tmpSum;
            answer = mid;
            break;
        }

        if (start > end)
            break;
    }

    cout << answer << endl;
}