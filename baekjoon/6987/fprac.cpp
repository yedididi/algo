#include <iostream>
#include <vector>

using namespace std;

typedef enum alpha_e {A = 0, B, C, D, E, F} alpha_t;

typedef struct s_node
{
    int win;
    int draw;
    int lose;
} t_node;

int isPossible = false;

bool checkAllSame(vector<t_node> answer, vector<t_node> guess)
{
    for (int i = A; i <= F; i++)
    {
        if (answer[i].win != guess[i].win)
            return (false);
        if (answer[i].draw != guess[i].draw)
            return (false);
        if (answer[i].lose != guess[i].lose)
            return (false);
    }
    return (true);
}

bool guessBiggerthanAnswer(vector<t_node> answer, vector<t_node> guess)
{
    for (int i = A; i <= F; i++)
    {
        if (answer[i].win < guess[i].win)
            return (false);
        if (answer[i].draw < guess[i].draw)
            return (false);
        if (answer[i].lose < guess[i].lose)
            return (false);
    }
    return (true);
}

void back(vector<t_node> answer, vector<t_node> guess, int depth)
{
    // printf("depth is:%d\n", depth);
    if (isPossible == true)
        return;

    if (depth == F)
    {
        // printf("depth is F\n");
        if (checkAllSame(answer, guess) == true)
            isPossible = true;
        return ;
    }
    else
    {
        if (guessBiggerthanAnswer(answer, guess) == false)
            return ;
    }
    
    for (int i = depth + 1; i <= F; i++)
    {
        //depth win
        guess[depth].win++;
        guess[i].lose++;
        back(answer, guess, depth + 1);
        guess[depth].win--;
        guess[i].lose--;

        //depth draw
        guess[depth].draw++;
        guess[i].draw++;
        back(answer, guess, depth + 1);
        guess[depth].draw--;
        guess[i].draw--;

        //depth lose
        guess[depth].lose++;
        guess[i].win++;
        back(answer, guess, depth + 1);
        guess[depth].lose--;
        guess[i].win--;
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

            guess[j].win = 0;
            guess[j].draw = 0;
            guess[j].lose = 0;
        }
        back(answer, guess, A);
        printf("ispossible:%d\n", isPossible);
        isOK.push_back(isPossible);
    }

    for (int i = 0; i < 4; i++)
        cout << isOK[i] << " ";
}

