#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, l, r;
vector<vector<int>> population(55, vector<int>(55, 0));
bool extVisited[55][55];
bool flag = false;
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};

void printMap()
{
    cout << "\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << population[i][j] << " ";
        cout << "\n";
    }
}

void bfs(int startI, int startJ)
{
    int populationSum = 0;
    int countryCount = 0;
    bool internalVisited[55][55];
    queue<pair<int, int>> q;
    q.push(make_pair(startI, startJ));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            internalVisited[i][j] = false;
    }

    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();

        for (int index = 0; index < 4; index++)
        {
            int newI = poppedNode.first + iNum[index];
            int newJ = poppedNode.second + jNum[index];
            int difference = abs(population[poppedNode.first][poppedNode.second] - population[newI][newJ]);

            // if (newI == 2 && newJ == 2)
            // {
            //     cout << "difference:" << difference << endl;
            // }

            if (newI <= 0 || newI > n || newJ <= 0 || newJ > n)
                continue;
            if (internalVisited[newI][newJ] || extVisited[newI][newJ]) //should i check internalVisited too?
                continue;
            if (difference < l || difference > r)
                continue;

            extVisited[newI][newJ] = true;
            internalVisited[newI][newJ] = true;
            populationSum += population[newI][newJ];
            countryCount++;
            flag = true;

            q.push(make_pair(newI, newJ));
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (internalVisited[i][j] == true)
                population[i][j] = populationSum / countryCount;
        }
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
        //bfs로 이어진 부분에 대해서 sum 전역변수로 구하기
        //sum 매번 초기화, 방문할 때마다 bfs 함수 내 visited, 전역 visited true
        //이때 방문 한번이라도 했으면 전역 flag true로 설정
        //while(!empty()) 끝나면 내부 visited true인 칸 다 sum/num
        //전역 visited false인 칸에 대해 bfs 돌리기
        //칸 마지막에 도달하면 전역 visited false로 초기화
        //flag false면 break, true면 count++하고 초기화 후 다음 while

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                extVisited[i][j] = false;
        }

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
        // printMap();
    }

    cout << count << endl;
}