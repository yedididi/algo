#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, w;
vector<int> answer;

typedef struct s_node
{
    int mvCount;
    int carOneI;
    int carOneJ;
    int carTwoI;
    int carTwoJ;
} t_node;

int main(void)
{
    int oneI = 1, oneJ = 1;
    cin >> n >> w;
    int twoI = n, twoJ = n;
    int dist = 0;
    t_node arr[1001][2];

    int a, b;
    cin >> a >> b;
    arr[0][0] = {a + b - 2, a, b, w, w};
    arr[0][1] = {2 * w - (a + b), 1, 1, a, b};

    for (int i = 1; i < w; i++)
    {
        int accidentI, accidentJ;

        cin >> accidentI >> accidentJ;

        int zeroDist = min(abs(arr[i - 1][0].carOneI - accidentI) + abs(arr[i - 1][0].carOneJ - accidentJ), 
            abs(arr[i - 1][0].carTwoI - accidentI) + abs(arr[i - 1][]));
        arr[i][0] = {}
        
        int oneDist = 
        arr[i][1] = {}
    }

    cout << dist << "\n";
    for (vector<int>::iterator itr = answer.begin(); itr != answer.end(); itr++)
    {
        cout << *itr << "\n";
    }
}