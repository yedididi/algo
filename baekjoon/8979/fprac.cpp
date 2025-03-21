#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n, k;

typedef struct s_medals
{
    int num;
    int gold;
    int silver;
    int bronze;
    int sum;
} t_medals;

vector<t_medals> list;
multimap<int, int> medalNum;

int main(void)
{
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        int num, gold, silver, bronze;

        cin >> num >> gold >> silver >> bronze;

        t_medals tmp = {num, gold, silver, bronze, gold + silver + bronze};
        list.push_back(tmp);
        medalNum.insert(gold + silver + bronze, num);
    }
}