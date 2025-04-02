#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct s_body
{
    int height;
    int weight;
} t_body;

bool compare(const t_body &a, const t_body &b)
{
    if (a.weight < b.weight && a.height < b.height)
        return (true);
    return (false);
}

int main(void)
{
    int n;
    int num = 0;
    cin >> n;

    vector<t_body> body(n);

    for (int i = 0; i < n; i++)
    {
        cin >> body[i].weight >> body[i].height;
    }

    for (int i = 0; i < n; i++)
    {
        int rank = 1;
        for (int j = 0; j < n; j++)
        {
            if (compare(body[i], body[j]))
                rank++;
        }
        cout << rank << " ";
    }
    cout << endl;
}