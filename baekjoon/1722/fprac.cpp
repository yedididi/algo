#include <iostream>
#include <set>

using namespace std;

int n;
int arr[21];
long long k;
set<long long> numbers;
long long factorial[21];

void precomputeFactorials() {
    factorial[0] = 1;
    for (int i = 1; i <= 20; i++)
        factorial[i] = factorial[i - 1] * i;
}

long long getFactorial(int num) {
    return factorial[num];
}

void printPermutation(long long input)
{
    for (int i = 0; i < n; i++)
    {
        int pNum = 0;
        long long factNum = getFactorial(n - i - 1);

        pNum = input / factNum;
        input = input % factNum;
        // cout << "calculated pNum is:" << pNum << endl;

        int rightNum = 0;
        for (set<long long>::iterator itr = numbers.begin(); itr != numbers.end(); itr++)
        {
            if (pNum == rightNum)
            {
                cout << *itr << " ";
                numbers.erase(*itr);
                break;
            }
            rightNum++;
        }
    }
    cout << endl;
}

void printWhichPermutation()
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
    {
        long long p = 1;
        for (set<long long>::iterator itr = numbers.begin(); itr != numbers.end(); itr++)
        {
            if (*itr == arr[i])
                break;
            p++;
        }
        sum += ((p - 1) * getFactorial(n - i - 1));
        numbers.erase(arr[i]);
    }
    cout << sum + 1 << endl;
}

int main(void)
{
    int problemType;
    bool visited[21] = {false, };
    long long permutation[21] = {0, };
    cin >> n >> problemType;

    precomputeFactorials();
    if (problemType == 1)
    {
        cin >> k;
        for (int i = 0; i < n; i++)
        {
            numbers.insert(i + 1);
        }
        printPermutation(k - 1);
    }
    else if (problemType == 2)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            numbers.insert(arr[i]);
        }
        printWhichPermutation();
    }
}