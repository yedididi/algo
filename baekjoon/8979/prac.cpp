#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Medal 
{
    int num;
    int gold;
    int silver;
    int bronze;
};

bool compare(const Medal &a, const Medal &b) 
{
    if (a.gold != b.gold) 
        return a.gold > b.gold;     // 금메달 내림차순

    if (a.silver != b.silver) 
        return a.silver > b.silver; // 은메달 내림차순

    return a.bronze > b.bronze;   // 동메달 내림차순
}

int main() 
{
    int n, k;
    cin >> n >> k;
    
    vector<Medal> countries(n);
    
    for (int i = 0; i < n; i++) 
    {
        cin >> countries[i].num >> countries[i].gold >> countries[i].silver >> countries[i].bronze;
    }

    sort(countries.begin(), countries.end(), compare);

    int rank = 1;  // 1등부터 시작
    for (int i = 0; i < n; i++) 
    {
        if (i > 0 && countries[i].gold == countries[i - 1].gold &&
            countries[i].silver == countries[i - 1].silver &&
            countries[i].bronze == countries[i - 1].bronze) 
        {
        } 
        else 
        {
            rank = i + 1;
        }

        if (countries[i].num == k) 
        {
            cout << rank << endl;
            break;
        }
        // cout << rank << endl;
    }
    return 0;
}
