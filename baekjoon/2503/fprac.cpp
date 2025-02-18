#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef struct s_node
{
    int number;
    int strike;
    int ball;
    int firstNumQuestion;
    int secondNumQuestion;
    int thirdNumQuestion;
} t_node;

int n;
vector<int> answer;
vector<t_node> question;
bool print = false;

bool allNumDiff(int input)
{
    int firstNum = input % 10;
    int secondNum = (input / 10) % 10;
    int thirdNum = input / 100;

    if (firstNum == secondNum)
        return (false);
    if (firstNum == thirdNum)
        return (false);
    if (thirdNum == secondNum)
        return (false);
    return (true);
}

bool questionOK(int num)
{
    int firstNum = num % 10;
    int secondNum = (num / 10) % 10;
    int thirdNum = num / 100;

    for (int i = 0; i < n; i++)
    {
        int strike = 0;
        int ball = 0;

        if (firstNum == question[i].firstNumQuestion) strike++;
        if (secondNum == question[i].secondNumQuestion) strike++;
        if (thirdNum == question[i].thirdNumQuestion) strike++;

        set<int> numbers;
        int numArr[6] = {firstNum, secondNum, thirdNum, question[i].firstNumQuestion, question[i].secondNumQuestion, question[i].thirdNumQuestion};
        for (auto i = 0; i < 6; i++)
            numbers.insert(numArr[i]);

        ball = 6 - numbers.size() - strike;

        // if (print == true)
        // {
        //     cout << "strike:" << strike << ", q.strike:" << question[i].strike << endl;
        //     cout << "ball:" << ball << ", q.ball:" <<  question[i].ball << endl;
        //     print = false;
        // }

        if (strike == question[i].strike && ball == question[i].ball)
        {
            // cout << "strike:" << strike << ", q.strike:" << question[i].strike << endl;
            // cout << "ball:" << ball << ", q.ball:" <<  question[i].ball << endl;
        }
        else
            return (false);
    }
    return (true);
}

void input(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        t_node tmp;
        cin >> tmp.number >> tmp.strike >> tmp.ball;
        tmp.firstNumQuestion = tmp.number % 10;
        tmp.secondNumQuestion = (tmp.number / 10) % 10;
        tmp.thirdNumQuestion = tmp.number / 100;
        question.push_back(tmp);
    }
}

int main(void)
{
    input();

    for (int i = 123; i <= 987; i++)
    {
        // if (i == 324)
        //     print = true;

        if (allNumDiff(i))
        {
            if (questionOK(i))
            {
                // cout << "qOK true\n";
                // printf("%d ok\n", i);
                answer.push_back(i);
            }
        }
    }
    cout << answer.size() << endl;
}