//예술성
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void input(void);

int n = 0, sum = 0;
int iNum[4] = {0, 0, 1, -1};
int jNum[4] = {1, -1, 0, 0};
vector<vector<int>>  map(30, vector<int>(30, 0));

typedef struct s_groupInfo
{
    int groupNum;
    int groupMemberCount;
    int groupRealNum;
} t_groupInfo;

void fillGroups(vector<vector<int>> &groups, vector<t_groupInfo> &groupInfos, int groupNum, int startI, int startJ)
{
    int groupMemberCount_ = 1;
    queue<pair<int, int>> q;

    q.push(make_pair(startI, startJ));
    groups[startI][startJ] = groupNum;

    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();
        int oldI = poppedNode.first;
        int oldJ = poppedNode.second;

        for (int index = 0; index < 4; index++)
        {
            int newI = oldI + iNum[index];
            int newJ = oldJ + jNum[index];

            if (newI < 0 || newI >= n || newJ < 0 || newJ >= n) continue;
            if (map[newI][newJ] != map[startI][startJ]) continue;

            groups[newI][newJ] = groupNum;
            groupMemberCount_++;
        }
    }
    t_groupInfo newGroupInfo = {groupNum, groupMemberCount_, map[startI][startJ]};
    groupInfos.push_back(newGroupInfo);
}

int getScore(void)
{
    int currentScore = 0;
    int groupNum = 1;
    vector<vector<int>> groups(30, vector<int>(30, 0));
    vector<t_groupInfo> groupInfos;
    vector<vector<int>> neiboringLines(30, vector<int>(30, 0));

    //seperate
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (groups[i][j] != 0)
            {
                fillGroups(groups, groupInfos, groupNum, i, j);
                groupNum++;
            }
        }
    }

    //get neighboring lines
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int index = 0; index < 4; index++)
            {
                int newI = i + iNum[index];
                int newJ = j + jNum[index];
                
                if (newI < 0 || newI >= n || newJ < 0 || newJ >= n) continue;

                if (groups[i][j] != groups[newI][newJ]) continue;

                neiboringLines[groups[i][j]][groups[newI][newJ]]++;
                // neiboringLines[groups[newI][newJ]][groups[i][j]]++;
            }
        }
    }

    //calculate score
    for (int i = 1; i < groupNum; i++)
    {
        for (int j = i + 1; j < groupNum; j++)
        {
            currentScore = currentScore + (groupInfos[i - 1].groupMemberCount + groupInfos[j - 1].groupMemberCount) * groupInfos[i - 1].groupRealNum * groupInfos[j - 1].groupRealNum * neiboringLines[i][j];
        }
    }
    sum += currentScore;
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