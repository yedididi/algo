#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int t, p, r, c;
vector<vector<int>> map;
vector<vector<int>> rotateInfo;
pair<int, int> ratCoordinate;
int globalTime = 0;

void input(void);

pair<int, int> chooseCheese(void)
{
    
}

int main(void)
{
    int k;
    cin >> k;

    for (int testCase = 1; testCase <= k; testCase++)
    {
        input();
        cout << "#" << testCase << " ";
        for (int time = 0; time < t; time++)
        {
            pair<int, int> chosenCheese = chooseCheese();
            moveRat(chosenCheese);
            rotateMap();
            globalTime++;
            cout << ratCoordinate.first << " " << ratCoordinate.second;
        }
        cout << "\n";
    }
}

void input(void)
{
    globalTime = 0;
    cin >> t >> p >> r >> c;

    map.resize(p * r, vector<int>(p * c, 0));
    map.resize(r, vector<int>(c, 0));

    for (int i = 0; i < p * r; i++)
    {
        for (int j = 0; j < p * c; j++)
            cin >> map[i][j];
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cin >> rotateInfo[i][j];
    }
    cin >> ratCoordinate.first >> ratCoordinate.second;
}