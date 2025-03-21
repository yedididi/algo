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
int sum[1000001] = {0,};
int maxSum = 0;
t_medals kMedals;
int countriesBeforeK = 0;

void input(void)
{
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        int num, gold, silver, bronze;

        cin >> num >> gold >> silver >> bronze;

        t_medals tmp = {num, gold, silver, bronze, gold + silver + bronze};
        list.push_back(tmp);

        sum[gold + silver + bronze]++;

        if (num == k)
            kMedals = tmp;
        if (maxSum < gold + silver + bronze)
            maxSum = gold + silver + bronze;
    }

    for (int i = maxSum; i > kMedals.sum; i--)
    {
        countriesBeforeK += sum[i];
    }
}

int main(void)
{
    input();

    for (int i = 0; i < n; i++)
    {
        if (list[i].sum == kMedals.sum && list[i].gold > kMedals.gold)
            countriesBeforeK++;
    // }
    // for (int i = 0; i < n; i++)
    // {
        if (list[i].sum == kMedals.sum && list[i].gold == kMedals.gold
            && list[i].silver > kMedals.silver)
            countriesBeforeK++;
    // }
    // for (int i = 0; i < n; i++)
    // {
        if (list[i].sum == kMedals.sum && list[i].gold == kMedals.gold && list[i].silver == kMedals.silver
            && list[i].bronze > kMedals.bronze)
            countriesBeforeK++;
    }
    cout << countriesBeforeK + 1 << endl;
}

// 6 5
// 1 3 0 0
// 2 0 2 0
// 3 0 0 2
// 4 0 2 0
// 5 6 3 2
// 6 0 0 0