#include <iostream>
#include <vector>

using namespace std;

typedef struct s_node
{
    int win;
    int draw;
    int lose;
} t_node;

bool back(int win, int draw, int lose)
{
    

    for (int i = 0; i < 5; i++)
    {
        back(win + 1, draw, lose);
        back(win, draw + 1, lose);
        back(win, draw, lose + 1);
    }
}

int main(void)
{
    vector<bool> isOK;

    for (int i = 0; i < 4; i++)
    {
        vector<t_node> results(6);
        vector<string> resultString;
        for (int j = 0; j < 6; j++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            results[j].win = a;
            results[j].draw = b;
            results[j].lose = c;
            resultString[j] = "";
        }
        isOK.push_back(back(0, 0, 0));
    }

    for (int i = 0; i < 4; i++)
        cout << isOK[i] << " ";
}