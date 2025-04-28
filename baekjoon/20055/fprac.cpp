#include <iostream>
#include <deque>

using namespace std;

typedef struct s_node 
{
    int durability;
    bool robot;
} t_node;

int n, k;
deque<t_node> upperBelt;
deque<t_node> lowerBelt;
int level = 0;
int zeroDurability = 0;

void input()
{
    cin >> n >> k;
   
    for (int i = 0; i < n; i++)
    {
        int tmp;

        cin >> tmp;
        t_node tmpNode = {tmp, 0};
        upperBelt.push_back(tmpNode);
    }

    for (int i = 0; i < n; i++)
    {
        int tmp;

        cin >> tmp;
        t_node tmpNode = {tmp, 0};
        lowerBelt.push_back(tmpNode);
    }
}

void rotateBelt()
{
    t_node upperPoppedNode = upperBelt.back();
    upperBelt.pop_back();

    lowerBelt.push_front(upperPoppedNode);

    t_node lowerPoppedNode = lowerBelt.back();
    lowerBelt.pop_back();

    upperBelt.push_front(lowerPoppedNode);

    if (upperBelt[n - 1].robot)
        upperBelt[n - 1].robot = false;
}

void moveRobot()
{
    for (int i = n - 2; i >= 0; i--) // n-1칸은 내리는 칸이라 어차피 이동 안 함
    {
        if (upperBelt[i].robot)
        {
            if (upperBelt[i + 1].robot == false && upperBelt[i + 1].durability > 0)
            {
                upperBelt[i].robot = false;
                upperBelt[i + 1].robot = true;
                upperBelt[i + 1].durability--;
                if (upperBelt[i + 1].durability == 0)
                    zeroDurability++;
            }
        }
    }

    // 추가: 이동 후에도 내리는 위치에 로봇 있으면 내려야 함
    if (upperBelt[n-1].robot)
        upperBelt[n-1].robot = false;
}

void putRobot()
{
    if (upperBelt[0].durability > 0)
    {
        upperBelt[0].robot = true;
        upperBelt[0].durability--;
        if (upperBelt[0].durability == 0)
            zeroDurability++;
    }
}

int main(void)
{
    input();

    while (zeroDurability != k)
    {
        level++;
        rotateBelt();
        moveRobot();
        putRobot();
    }
    cout << level << endl;
}