#include <iostream>
#include <vector>

using namespace std;

int computerNum, lineNum;
vector<vector<int>> map(100, vector<int>(0));
vector<bool> visited(100, 0);
int totalNum = 0;

void dfs(int comNum)
{
    for (int i = 0; i < map[comNum].size(); i++)
    {
        if (visited[map[comNum][i]])
            continue;

            totalNum++;
        visited[map[comNum][i]] = true;
        dfs(map[comNum][i]);
    }
}

int main(void)
{
    cin >> computerNum >> lineNum;

    for (int i = 0; i < lineNum; i++)
    {
        int a, b;
        cin >> a >> b;
        map[a].push_back(b);
        map[b].push_back(a);
    }

    visited[1] = true;
    dfs(1);
    cout << totalNum << endl;
}