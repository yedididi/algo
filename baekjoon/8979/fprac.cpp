#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct s_medal
{
    int num;
    int gold;
    int silver;
    int bronze;
} t_medal;

int n, k;

bool compare(const t_medal &a, const t_medal &b)
{
    if (a.gold != b.gold)
        return (a.gold > b.gold);
    
    if (b.silver != b.silver)
        return (a.silver > b.silver);
    
    return (a.bronze > b.bronze);
}

int main(void)
{
    cin >> n >> k;

    vector<t_medal> score(n);

    for (int i = 0; i < n; i++)
    {
        cin >> score[i].num >> score[i].gold >> score[i].silver >> score[i].bronze;
    }

    sort(score.begin(), score.end(), compare);

    int rank = 1;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && (score[i].gold == score[i - 1].gold) && (score[i].silver == score[i - 1].silver) && (score[i].bronze == score[i - 1].bronze))
            ;
        else
            rank = i + 1;

        cout << rank << endl;
        // if (score[i].num == k)
        // {
        //     cout << rank << endl;
        //     break;
        // }
    }
}