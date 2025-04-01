#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct s_body
{
    int height;
    int weight;
    int rank;
    int num;
} t_body;

int n;

bool compare(const t_body &a, const t_body &b)
{
    if (a.height != b.height)
        return (a.weight > b.weight);
    return (a.weight > b.weight);
}

bool finalCompare(const t_body &a, const t_body &b)
{
    return (a.num < b.num);
}

int main(void)
{
    int num = 0;
    cin >> n;

    vector<t_body> body(n);

    for (int i = 0; i < n; i++)
    {
        cin >> body[i].weight >> body[i].height;
        body[i].num = num++;
    }

    sort(body.begin(), body.end(), compare);

    int rank = 1;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && body[i].height < body[i - 1].height && body[i].weight < body[i - 1].weight)
            rank = i + 1;
        else
            ;
        
        body[i].rank = rank;
        // cout << rank << " ";
    }

    sort(body.begin(), body.end(), finalCompare);


    for (int i = 0; i < n; i++)
    {
        cout << body[i].rank << " ";
    }
    cout << endl;
}