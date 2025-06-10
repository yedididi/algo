//예술성
#include <iostream>
#include <vector>

using namespace std;

void input(void);

int n = 0, sum = 0;
vector<vector<int>>  map(30, vector<int>(30, 0));

int getScore(void)
{

}

void rotate(void)
{

}

int main(void)
{
    input();
    
    getScore();
    for (int i = 0; i < 3; i++)
    {
        rotate();
        getScore();
    }
    cout << sum << "\n";
}

void input(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
}