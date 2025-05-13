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


typedef struct s_profile
{
    std::string name = "이예지";
	int         birthday = 19991216;
    std::string github = "https://github.com/yedididi";
    std::string velog = "https://velog.io/@yedididi/posts";
    std::string phone = "010-8591-7245";
    std::string email = "curry1115@naver.com";
    std::string address = "서울시 광진구 능동로16길"
} t_profile;