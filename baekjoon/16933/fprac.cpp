#include <iostream>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

int n, m, k;
int map[1000][1000];
bool visited[1000][1000][10] = {0, };
int iNum[4] = {1, -1, 0, 0};
int jNum[4] = {0, 0, 1, -1};

enum time_e {DAY = 0, NIGHT = 1};

int bfs()
{
    queue<tuple<int, int, int, int, int>> q;

    q.push(make_tuple(0, 0, k, 1, DAY));
    visited[0][0][0] = true;

    while (!q.empty())
    {
        int i_, j_, k_, mvCount_;
        bool time_;
        tie(i_, j_, k_, mvCount_, time_) = q.front();
        q.pop();

        if (i_ == n - 1 && j_ == m - 1)
            return (mvCount_);

        for (int index = 0; index < 4; index++)
        {
            int newI = i_ + iNum[index];
            int newJ = j_ + jNum[index];

            if (newI < 0 || newI >= n || newJ < 0 || newJ >= m || visited[newI][newJ][k - k_])
                continue;

            if (map[newI][newJ] == 1 && k_ > 0)
            {
                if (time_ == DAY)
                {
                    q.push(make_tuple(newI, newJ, k_ - 1, mvCount_ + 1, !time_));
                    visited[newI][newJ][k - k_] = true;
                }
                else if (time_ == NIGHT)
                    q.push(make_tuple(i_, j_, k_, mvCount_ + 1, !time_)); 
            }
            else if (map[newI][newJ] == 0)
            {
                q.push(make_tuple(newI, newJ, k_, mvCount_ + 1, !time_));
                visited[newI][newJ][k - k_] = true;
            }
        }
    }
    return (-1);
}

int main(void)
{
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++)
            map[i][j] = tmp[j] - '0';
    }

    cout << bfs() << endl;
}