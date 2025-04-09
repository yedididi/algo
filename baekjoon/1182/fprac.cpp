#include <iostream>
#include <vector>

using namespace std;

vector<int> numbers;
vector<int> subset;
int n, s;
int total = 0;

int getSum(void)
{
    int sum = 0;

    for (vector<int>::iterator itr = subset.begin(); itr != subset.end(); itr++)
    {
        sum += *itr;
    }
    return (sum);
}

void dfs(int depth)
{
    if (depth == n)
    {
        if (getSum() == s)
        {
            if (subset.size() != 0)
                total++;
        }
        return ;
    }

    dfs(depth + 1);

    subset.push_back(numbers[depth]);
    dfs(depth + 1);
    subset.pop_back();
}

int main(void)
{
    vector<int> subset;
    cin >> n >> s;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }

    dfs(0);
    cout << total << endl;
}