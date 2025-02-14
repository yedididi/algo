#include <iostream>
#include <vector>

using namespace std;

typedef struct s_node
{
    int win;
    int draw;
    int lose;
} t_node;

int isPossible = false;

bool back(vector<t_node> answer, vector<t_node> guess)
{
    
    for (int i = 0; i < 5; i++)
    {
        guess[i].win++;
        back(answer, guess);
        guess[i].win--;

        guess[i].draw++;
        back(answer, guess);
        guess[i].draw--;

        guess[i].lose++;
        back(answer, guess);
        guess[i].lose--;
    }
}

int main(void)
{
    vector<bool> isOK;

    for (int i = 0; i < 4; i++)
    {
        vector<t_node> answer(6);
        vector<t_node> guess(6);
        isPossible = false;
        for (int j = 0; j < 6; j++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            answer[j].win = a;
            answer[j].draw = b;
            answer[j].lose = c;

            answer[j].win = 0;
            answer[j].draw = 0;
            answer[j].lose = 0;
        }
        back(answer, guess);
        isOK.push_back(isPossible);
    }

    for (int i = 0; i < 4; i++)
        cout << isOK[i] << " ";
}