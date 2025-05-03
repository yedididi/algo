#include <iostream>

using namespace std;

int n;
char map[1001][1001];
int heartI = 0, heartJ = 0, leftArm = 0, rightArm = 0, waist = 0, leftLeg = 0, rightLeg = 0;
bool flag = true;

void input()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (flag == true && map[i][j] == '*')
            {
                heartI = i + 1;
                heartJ = j;
                flag = false;
            }
        }
    }
}

void getLength()
{
    for (int index = heartJ + 1; index < n; index++)
    {
        if (map[heartI][index] == '*')
            rightArm++;
        else
            break;
    }


    for (int index = heartJ - 1; index >= 0; index--)
    {
        if (map[heartI][index] == '*')
            leftArm++;
        else
            break;
    }

    int waistEndI = 0;

    for (int index = heartI + 1; index < n; index++)
    {
        if (map[index][heartJ] == '*')
            waist++;
        else
        {
            waistEndI = index;
            break;
        }
    }

    for (int index = waistEndI; index < n; index++)
    {
        if (map[index][heartJ - 1] == '*')
            leftLeg++;
        else
            break;
    }

    for (int index = waistEndI; index < n; index++)
    {
        if (map[index][heartJ + 1] == '*')
            rightLeg++;
        else
            break;
    }
}

int main(void)
{
    input();
    getLength();
    cout << heartI + 1 << " " << heartJ + 1 << endl;
    cout << leftArm << " " << rightArm << " " << waist << " " << leftLeg << " " << rightLeg << endl;
}