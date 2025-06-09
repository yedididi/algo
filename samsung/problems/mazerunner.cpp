#include <iostream>
#include <vector>

using namespace std;

int playerTotalCount;
pair<int, int> exitCoordinate;
vector<pair<int, int>> playerCoordinates;
vector<vector<int>> map(11, vector<int>(11, 0));
int totalMoveCount = 0;
int n, k;

void input(void)
{
    cin >> n >> playerTotalCount >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    }

    for (int i = 0; i < playerTotalCount; i++)
    {
        int a, b;
        cin >> a >> b;
        playerCoordinates.push_back(make_pair(a, b));
        map[a][b] = 'P';
    }

    int a, b;
    cin >> a >> b;
    exitCoordinate.first = a;
    exitCoordinate.second = b;
    map[a][b] = 'E';
}

int main(void)
{
    input();
}   