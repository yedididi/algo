#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> arr;
int weight = 0;
int num = 0;

bool compare(int a, int b)
{
    return (a > b);
}

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tmp;

        cin >> tmp;
        arr.push_back(tmp);
    }
    sort(arr.begin(), arr.end(), compare);

    for (auto itr = arr.begin(); itr != arr.end(); itr++)
    {
        num++;
        weight = max(weight, num * *itr);
    }
    cout << weight << endl;
}