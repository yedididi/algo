#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, l, r;
vector<vector<int>> population(55, vector<int>(55, 0));
bool extVisited[55][55];
bool flag = false;
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};

void bfs(int startI, int startJ)
{
    int populationSum = 0;
    int countryCount = 0;
    queue<pair<int, int>> q;
    vector<pair<int, int>> unionCountries;
    q.push(make_pair(startI, startJ));

    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.first + iNum[index];
            int newJ = poppedNode.second + jNum[index];
            int difference = abs(population[poppedNode.first][poppedNode.second] - population[newI][newJ]);

            if (newI <= 0 || newI > n || newJ <= 0 || newJ > n)
                continue;
            if (extVisited[newI][newJ])
                continue;
            if (difference < l || difference > r)
                continue;

            extVisited[newI][newJ] = true;
            unionCountries.push_back(make_pair(newI, newJ));
            populationSum += population[newI][newJ];
            countryCount++;
            flag = true;

            q.push(make_pair(newI, newJ));
        }
    }

    for (auto itr = unionCountries.begin(); itr != unionCountries.end(); itr++)
    {
        population[itr->first][itr->second] = populationSum / countryCount;
    }
}

int main(void)
{
    int count = 0;
    cin >> n >> l >> r;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> population[i][j];
        }
    }

    while (1)
    {
        memset(extVisited, 0, sizeof(extVisited));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (extVisited[i][j])
                    continue;
    
                bfs(i, j);
            }
        }

        if (flag == false)
            break;
        
        count++;
        flag = false;
    }

    cout << count << endl;
}