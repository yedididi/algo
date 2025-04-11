#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

typedef struct s_node
{
    int start;
    int end;
    int lenth;
} t_node;

int n, d, minValue = 2147483647;
vector<t_node> shortcut;

void dfs(int location, int shortcutIndex, int distance)
{
    // cout << "location is:" << location << endl;
    if (distance >= minValue || location > d)
        return ;

    if (location >= d)
    {
        // cout << "distance is:" << distance << endl;
        if (location == d)
            minValue = min(minValue, distance);
        return ;
    }

    for (int index = shortcutIndex; index != n; index++)
    {
        dfs(shortcut[index].end, index + 1, distance + shortcut[index].lenth);
        dfs(location + 1, index, distance + 1);
    }
}

bool compare(t_node &a, t_node &b)
{
    if (a.start < b.start)
        return (true);
    return (false);
}

int main(void)
{
    cin >> n >> d;

    for (int i = 0; i < n; i++)
    {
        t_node tmp;
        cin >> tmp.start >> tmp.end >> tmp.lenth;
        shortcut.push_back(tmp);
    }

    sort(shortcut.begin(), shortcut.end(), compare);

    // for (auto itr = shortcut.begin(); itr != shortcut.end(); itr++)
    //     cout << itr->start << " ";
    // cout << endl;

    dfs(0, 0, 0);
    cout << minValue << endl;
}