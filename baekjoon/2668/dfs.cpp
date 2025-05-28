#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
vector<int> numbers(101);
vector<int> answer;
bool visited[101];

void dfs(int start, int curr)
{
    if (visited[curr])
    {
        if (start == curr)
            answer.push_back(curr);
        return;
    }

    visited[curr] = true;
    dfs(start, numbers[curr]);
}

int main(void)
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> numbers[i]; 
    }

    for (int i = 1; i <= n; i++)
    {
        memset(visited, 0, 101);
        dfs(i, i);
    }

    cout << answer.size() << "\n";
    for (auto x : answer) 
        cout << x << "\n";
}