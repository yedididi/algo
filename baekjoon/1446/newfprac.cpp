#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct s_node
{
    int start;
    int end;
    int lenth;
} t_node;

int n, d, minValue = 2147483647;
vector<t_node> shortcut;

int main(void)
{
    cin >> n >> d;

    for (int i = 0; i < n; i++)
    {
        t_node tmp;
        cin >> tmp.start >> tmp.end >> tmp.lenth;
        shortcut.push_back(tmp);
    }
}
