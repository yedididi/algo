#include <iostream>
#include <algorithm>

using namespace std;

int n;
int map[130][130];
int minValue = 2147483647;
bool visited[130][130];
typedef struct s_node
{
    int i;
    int j;
    int sum;
} t_node;

int iNum[4] = {0, 0, -1, 1};
int jNum[4] = {1, -1, 0, 0};

void getMinRupy(int i, int j, int sum)
{
    if (i == (n - 1) && j == (n - 1))
    {
        minValue = min(sum, minValue);
        return ;
    }

    for (int index = 0; index < 4; index++)
    {
        int newI = i + iNum[index];
        int newJ = j + jNum[index];

        if (newI < 0 || newI >= n || newJ < 0 || newJ >= n || visited[newI][newJ])
            continue;
        
        if (sum + map[newI][newJ] >= minValue)
            continue;
        
        visited[newI][newJ] = true;
        getMinRupy(newI, newJ, sum + map[newI][newJ]);
        visited[newI][newJ] = false;
    }
    
}

int main(void)
{
    int count = 1;

    while (1)
    {
        cin >> n;

        if (n == 0)
            break;
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                
                cin >> tmp;
                map[i][j] = tmp;
                visited[i][j] = 0;
            }
        }
        minValue = 2147483647;
        visited[0][0] = true;
        getMinRupy(0, 0, map[0][0]);
        cout << "Problem " << count << ": " << minValue << "\n";
        count++;
    }
}
