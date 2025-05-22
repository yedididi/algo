#include <iostream>
#include <queue>
#include <vector>

using namespace std;


int n, m, start, endNum;
int almostMin;

void getAlmostMinDist(vector<vector<int>> map)
{

}

int main(void)
{
    vector<int> answer;
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        
        cin >> start >> endNum;
        vector<vector<int>> map(endNum, vector<int>(endNum, -1));
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            map[a][b] = c;
            map[b][a] = c;
        }
        getAlmostMinDist(map);
        answer.push_back(almostMin);
    }
}